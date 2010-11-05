/* TestRun.cpp -- Information on one run of a test
 * Copyright (C) 2009 John Millikin
 * For conditions of distribution and use, see COPYING
 */

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
		String type_name = demangled_name;
		free(demangled_name);
		return type_name;
	}
	
	/* De-mangling the name failed */
	return name;
}

static String error_unknown_exception()
{
#if HAVE_CXA_CURRENT_EXCEPTION_TYPE
		std::type_info *info;
		info = ::abi::__cxa_current_exception_type ();
		
		/* Unhandled exception of type 'type' */
		return String::Build
			( "Unhandled exception of type '"
			, demangle_typename(info->name()).CStr()
			, "'", NULL
			);
#else
		return String::FromStatic("Unhandled exception with unknown type");
#endif
}

// }}}

// fork()-based test spawning {{{

static void write_message(int fd, const String &message)
{
	char buf[30];
	
	sprintf(buf, "%-10lu", message.Size());
	write(fd, buf, 10);
	write(fd, message.CStr(), message.Size());
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
	String retval(message, message_len);
	delete[] message;
	return retval;
}

static String read_token
	( const char *message
	, const char **out_next
	)
{
	char *next;
	unsigned int size;
	
	size = strtoul(message, &next, 10);
	next++; /* Skip the colon */
	
	/* Read the actual string */
	String token;
	if (size > 0)
	{
		token = String(next, size);
		next += size;
	}
	
	/* Skip whitespace */
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
	const char *c_message = message.CStr();
	
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
		
		line = strtoul(line_str.CStr(), NULL, 10);
		
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
	
	return new Error(message);
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
		out_error = new Error("Can't start test: pipe() returned -1");
		return;
	}
	
	if ((pid = fork()) == -1)
	{
		out_error = new Error("Can't start test: fork() returned -1");
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
			error_msg = String::Build
				( "Unhandled exception: "
				, e.what (), NULL
				);
		}
		
		catch (...)
		{
			error_msg = error_unknown_exception();
		}
		
		if (error_msg.Size() > 0)
		{
			result.send_error(error_msg);
		}
		
		int exit_code = 1;
		if (not result.self_error)
		{
			write_message
				( result.self_fd
				, String::FromStatic("4:pass")
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
			( String::NoCopy(text)
			, result.failure_message
			, String::NoCopy(file), line
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
		assert(AssertionResult::fail("Boolean assertion failed"),
		       text, file, line);
	}
}

void TestRun::fail
	( const char *message
	, const char *file
	, unsigned int line
	)
{
	String source = String::Build
		( "COPPER_FAIL("
		, repr(message).CStr()
		, ")"
		, NULL
		);
	send_fail
		( source
		, String::NoCopy(message)
		, String::NoCopy(file), line
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
	String text = String::Build
		( "throws (", exc_type, ", "
		, code, ")"
		, NULL
		);
	
	String message = String::Build
		("\"", code
		, "\" didn't throw an exception of type \""
		, exc_type, "\""
		, NULL
		);
	
	send_fail(text, message, String::NoCopy(file), line);
}

void TestRun::send_fail
	( const String &text
	, const String &message
	, const String &file
	, unsigned int line
	)
{
	self_error = true;
	
	/* 4:fail text line message */
	String line_str = repr(line),
	       line_len = repr(line_str.Size()),
	       text_len = repr(text.Size()),
	       file_len = repr(file.Size()),
	       message_len = repr(message.Size());
	
	String result = String::Build
		( "4:fail "
		, text_len.CStr(), ":", text.CStr()
		, line_len.CStr(), ":", line_str.CStr()
		, file_len.CStr(), ":", file.CStr()
		, message_len.CStr(), ":", message.CStr()
		, NULL
		);
	
	write_message(self_fd, result);
}

void TestRun::send_error(const String &message)
{
	self_error = true;
	
	/* 5:error message */
	/* Example: "5:error 18:segmentation fault" */
	String message_len = repr(message.Size());
	
	String result = String::Build
		("5:error "
		, message_len.CStr(), ":", message.CStr()
		, NULL
		);
	
	write_message(self_fd, result);
}

// }}}

TestRun::TestRun(int fd)
	: self_fd(fd)
	, self_error(false)
{
}

/** @class Failure
 * @brief Stores information on a failed assertion.
 */

/** @var Failure::Text
 * @brief The code that this Assertion tests.
 */

/** @var Failure::Message
 * @brief The human-readable failure message.
 */

/** @var Failure::File
 * @brief The name of the file containing the assertion.
 */

/** @var Failure::Line
 * @brief The line the assertion is located on.
 */

/**
 * @brief Create a new failure record.
 * 
 * @param text The code that was asserted.
 * @param message The human-readable failure message.
 * @param file The name of the file containing the assertion.
 * @param line The line the assertion is located on.
 */
Failure::Failure
	( const String &text
	, const String &message
	, const String &file
	, unsigned int line
	)
	: Text (text)
	, Message (message)
	, File (file)
	, Line (line)
{
}

/** @class Error
 * @brief Stores information on an unexpected error.
 * 
 * This is used to indicate that something unexpected went wrong
 * running a test. Errors should only be used for problems that
 * would not be expected.
 */

/** @var Error::Message
 * @brief The error that occurred.
 */

/**
 * @brief Initialize a new error.
 * 
 * @param message The error string.
 */
Error::Error(const String &message)
	: Message (message)
{
}

}
