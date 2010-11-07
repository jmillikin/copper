// Copyright (C) 2009-2010 John Millikin <jmillikin@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <copper/TestRun.hpp>
#include <copper/AssertionResult.hpp>
#include <copper/repr.hpp>
#include <copper/Test.hpp>

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctype.h>
#include <unistd.h>
#include <stdexcept>

#include <sys/types.h>
#include <sys/wait.h>

#if HAVE_CXA_CURRENT_EXCEPTION_TYPE
#	include <cxxabi.h>
#endif

using std::strtoul;
using std::strcmp;
using std::sprintf;
using std::sscanf;

namespace Copper {

// Exception parsing {{{

static String demangle_typename(const char *name)
{
	int demangle_status = -1;
	char *demangled_name = NULL;
	
#if HAVE_CXA_DEMANGLE
	demangled_name = ::abi::__cxa_demangle
		( name, NULL, NULL
		, &demangle_status
		);
#endif
	
	if (demangle_status == 0)
	{
		String type_name = String::copy(demangled_name);
		free(demangled_name);
		return type_name;
	}
	
	// De-mangling the name failed
	return String::copy(name);
}

static String error_unknown_exception()
{
#if HAVE_CXA_CURRENT_EXCEPTION_TYPE
		std::type_info *info;
		info = ::abi::__cxa_current_exception_type ();
		
		// Unhandled exception of type 'type'
		return String::build
			( "Unhandled exception of type '"
			, demangle_typename(info->name()).c_str()
			, "'", NULL
			);
#else
		return String::peek("Unhandled exception with unknown type");
#endif
}

// }}}

// fork()-based test spawning {{{

static void write_message(int fd, const String &message)
{
	char buf[30];
	
	sprintf(buf, "%-10lu", message.size());
	write(fd, buf, 10);
	write(fd, message.c_str(), message.size());
}

static String read_message(int fd)
{
	unsigned long message_len;
	char *message;
	char buf[30];
	
	read(fd, buf, 10);
	
	buf[10] = 0;
	
	sscanf(buf, "%lu ", &message_len);
	message = new char[message_len + 1];
	
	read(fd, message, message_len);
	return String::steal(message, message_len);
}

static String read_token
	( const char *message
	, const char **out_next
	)
{
	char *next;
	unsigned int size;
	
	size = strtoul(message, &next, 10);
	next++; // Skip the colon
	
	// Read the actual string
	String token;
	if (size > 0)
	{
		token = String::copy(next, size);
		next += size;
	}
	
	// Skip whitespace
	while (isspace(next[0])) { ++next; }
	
	if (out_next) { *out_next = next; }
	return token;
}

static void child_postmortem
	( int fd
	, Failure *&out_failure
	, Error *&out_error
	)
{
	String message = read_message(fd);
	const char *c_message = message.c_str();
	
	String type = read_token(c_message, &c_message);
	
	if (type == "pass")
	{ return; }
	
	if (type == "fail")
	{
		unsigned int line;
		
		String text     = read_token(c_message, &c_message),
		       line_str = read_token(c_message, &c_message),
		       file_str = read_token(c_message, &c_message),
		       message  = read_token(c_message, &c_message);
		
		line = strtoul(line_str.c_str(), NULL, 10);
		
		out_failure = new Failure(text, message, file_str, line);
	}
	
	else if (type == "error")
	{
		out_error = new Error(read_token(c_message, NULL));
	}
}

static Error *child_aborted(int status)
{
	const char *message = "Child terminated early";
	
	if (WIFSIGNALED (status))
	{
		int sig = WTERMSIG (status);
		
#if HAVE_STRSIGNAL
		message = strsignal (sig);
#elif HAVE_SYS_SIGLIST
		message = sys_siglist[sig];
#else
		message = "Unknown signal";
#endif
	}
	
	return new Error(String::copy(message));
}

void TestRun::run_test
	( Test &test
	, Failure *&out_failure
	, Error *&out_error
	)
{
	out_failure = NULL;
	out_error = NULL;
	
	pid_t pid;
	int pipes[2];
	
	if (pipe(pipes) == -1)
	{
		out_error = new Error(String::peek("Can't start test: pipe() returned -1"));
		return;
	}
	
	if ((pid = fork()) == -1)
	{
		out_error = new Error(String::peek("Can't start test: fork() returned -1"));
		close(pipes[0]);
		close(pipes[1]);
		return;
	}
	
	if (pid == 0)
	{
		close(pipes[0]);
		TestRun result(pipes[1]);
		
		String error_msg;
		try
		{
			test.Run(result);
		}
		catch (const std::exception &e)
		{
			error_msg = String::build
				( "Unhandled exception: "
				, e.what (), NULL
				);
		}
		
		catch (...)
		{
			error_msg = error_unknown_exception();
		}
		
		if (error_msg.size() > 0)
		{
			result.send_error(error_msg);
		}
		
		int exit_code = 1;
		if (not result.self_error)
		{
			write_message
				( result.self_fd
				, String::peek("4:pass")
				);
			exit_code = 0;
		}
		
		close(pipes[1]);
		exit(exit_code);
	}
	
	else
	{
		close(pipes[1]);
		
		int status;
		
		waitpid(pid, &status, 0);
		if (WIFEXITED (status))
		{
			child_postmortem(pipes[0], out_failure, out_error);
		}
		else
		{
			out_error = child_aborted(status);
		}
		close(pipes[0]);
	}
}

// }}}

// test callbacks {{{

void TestRun::assert
	( const Copper::AssertionResult &result
	, const char *text
	, const char *file
	, unsigned int line
	)
{
	if (not result.passed)
	{
		send_fail
			( String::peek(text)
			, result.message
			, String::peek(file), line
			);
	}
}

void TestRun::assert
	( bool result
	, const char *text
	, const char *file
	, unsigned int line
	)
{
	if (not result)
	{
		assert(AssertionResult::fail(String::peek("Boolean assertion failed")),
		       text, file, line);
	}
}

void TestRun::fail
	( const char *message
	, const char *file
	, unsigned int line
	)
{
	String source = String::build
		( "COPPER_FAIL("
		, repr(message).c_str()
		, ")"
		, NULL
		);
	send_fail
		( source
		, String::peek(message)
		, String::peek(file), line
		);
}

void
TestRun::fail_throws
	( const char *exc_type
	, const char *code
	, const char *file
	, unsigned int line
	)
{
	String text = String::build
		( "throws (", exc_type, ", "
		, code, ")"
		, NULL
		);
	
	String message = String::build
		("\"", code
		, "\" didn't throw an exception of type \""
		, exc_type, "\""
		, NULL
		);
	
	send_fail(text, message, String::peek(file), line);
}

void TestRun::send_fail
	( const String &text
	, const String &message
	, const String &file
	, unsigned int line
	)
{
	self_error = true;
	
	// 4:fail text line message
	String line_str = repr(line),
	       line_len = repr(line_str.size()),
	       text_len = repr(text.size()),
	       file_len = repr(file.size()),
	       message_len = repr(message.size());
	
	String result = String::build
		( "4:fail "
		, text_len.c_str(), ":", text.c_str()
		, line_len.c_str(), ":", line_str.c_str()
		, file_len.c_str(), ":", file.c_str()
		, message_len.c_str(), ":", message.c_str()
		, NULL
		);
	
	write_message(self_fd, result);
	exit(1);
}

void TestRun::send_error(const String &message)
{
	self_error = true;
	
	// 5:error message
	// Example: "5:error 18:segmentation fault"
	String message_len = repr(message.size());
	
	String result = String::build
		("5:error "
		, message_len.c_str(), ":", message.c_str()
		, NULL
		);
	
	write_message(self_fd, result);
	exit(1);
}

// }}}

TestRun::TestRun(int fd)
	: self_fd(fd)
	, self_error(false)
{
}

Failure::Failure
	( const String &text
	, const String &message
	, const String &file
	, unsigned int line
	)
	: text(text)
	, message(message)
	, file(file)
	, line(line)
{
}

Error::Error(const String &message)
	: message(message)
{
}

}
