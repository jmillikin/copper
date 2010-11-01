/* ForkingTestRunner.cpp -- Runs each test in a separate process
 * Copyright (C) 2009 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/ForkingTestRunner.hpp>
#include <copper/String.hpp>
#include <copper/Error.hpp>
#include <copper/Failure.hpp>
#include <copper/Formatters.hpp>
#include <copper/TestRun.hpp>
#include <copper/AssertionResult.hpp>
#include <copper/Test.hpp>
#include <copper/OutputHandler.hpp>

#include <cstring>
#include <cstdlib>
#include <cstdio>

#include <sys/types.h>
#include <sys/wait.h>

using Copper::String;
using Copper::Failure;
using Copper::Error;
using Copper::format;
using Copper::Test;

using std::strtoul;
using std::strcmp;
using std::sprintf;
using std::sscanf;

namespace {

String
SerializeFailure (const Failure &failure)
{
	/* 7:failure text line message */
	String line_str = format (failure.Line),
	       line_len = format (line_str.Size ()),
	       text_len = format (failure.Text.Size ()),
	       file_len = format (failure.File.Size ()),
	       message_len = format (failure.Message.Size ());
	
	return String::Build ("7:failure ",
	                      text_len.CStr (), ":",
	                      failure.Text.CStr (),
	                      
	                      line_len.CStr (), ":",
	                      line_str.CStr (),
	                      
	                      file_len.CStr (), ":",
	                      failure.File.CStr (),
	                      
	                      message_len.CStr (), ":",
	                      failure.Message.CStr (), NULL);
}

String
SerializeError (const Error &error)
{
	/* 5:error message */
	/* Example: "5:error 18:segmentation fault" */
	String message_len = format (error.Message.Size ());
	
	return String::Build ("5:error ",
	                      message_len.CStr (), ":",
	                      error.Message.CStr (), NULL);
}

String
SerializePass ()
{
	return String::FromStatic ("6:passed");
}

String
ParseToken (const char *message, const char **_next)
{
	char *next;
	unsigned int size;
	
	size = strtoul (message, &next, 10);
	next++; /* Skip the colon */
	
	/* Read the actual string */
	String token = String (next, size);
	next += size;
	
	/* Skip whitespace */
	while (isspace (next[0])) { ++next; }
	
	if (_next) { *_next = next; }
	return token;
}

void
Unserialize (const char *c_message, Failure **failure, Error **error)
{
	if (strcmp (c_message, "6:passed") == 0) { return; }
	
	String type = ParseToken (c_message, &c_message);
	
	if (type == "failure")
	{
		unsigned int line;
		
		String text     = ParseToken (c_message, &c_message),
		       line_str = ParseToken (c_message, &c_message),
		       file_str = ParseToken (c_message, &c_message),
		       message  = ParseToken (c_message, &c_message);
		
		line = strtoul (line_str.CStr (), NULL, 10);
		
		*failure = new Failure (text, message, file_str, line);
	}
	
	else if (type == "error")
	{
		*error = new Error (ParseToken (c_message, NULL));
	}
}

Error
ProcessError (int status)
{
	if (WIFSIGNALED (status))
	{
		int sig = WTERMSIG (status);
		char *message;
		
#if HAVE_STRSIGNAL
		message = strsignal (sig);
#elif HAVE_SYS_SIGLIST
		message = sys_siglist[sig];
#else
		message = "Unknown signal";
#endif
		return Error (message);
	}
	
	/* Child terminated for unknown reason */
	return Error ("Child terminated early");
}

void
WriteMessage (int fd, const String &message)
{
	char buf[30];
	
	sprintf (buf, "%-10u", message.Size ());
	write (fd, buf, 10);
	write (fd, message.CStr (), message.Size ());
}

class ForkedTestRun : public Copper::TestRun
{
public:
	ForkedTestRun (int pipe_fd, Test *test)
	: Copper::TestRun (test), fd (pipe_fd), got_error (false) {}
	
	virtual bool
	Assert (const Copper::AssertionResult &result,
	        const char *text,
	        const char *file,
	        unsigned int line)
	{
		if (result.passed) { return true; }
		return FailImpl (String::NoCopy (text),
		                 result.failure_message,
		                 String::NoCopy (file), line);
	}
	
	virtual bool
	Fail (const char *message,
	      const char *file,
	      unsigned int line)
	{
		return FailImpl (String (),
		                 String::NoCopy (message),
		                 String::NoCopy (file), line);
	}
	
	virtual bool
	AssertThrowsFailed (const char *exc_type,
	                    const char *code,
	                    const char *file,
	                    unsigned int line)
	{
		String text = String::Build ("throws (",
		                             exc_type, ", ",
		                             code, ")", NULL);
		String message = String::Build ("\"", code,
		                                "\" didn't throw an exception of type \"",
		                                exc_type, "\"", NULL);
		
		
		return FailImpl (text, message, String::NoCopy (file), line);
	}
	
	bool got_error;
	
private:
	bool
	FailImpl (const String &text,
	          const String &message,
	          const String &file,
	          unsigned int line)
	{
		Failure failure (text, message, file, line);
		WriteMessage (fd, SerializeFailure (failure));
		got_error = true;
		return false;
	}
	
	int fd;
};

void RunParent (Test *test, int fd, pid_t child_pid, Copper::OutputHandler *output)
{
	unsigned int message_len;
	char *message;
	int status;
	char buf[30];
	
	waitpid (child_pid, &status, 0);
	
	if (WIFEXITED (status))
	{
		status = read (fd, buf, 10);
		
		buf[10] = 0;
		
		sscanf (buf, "%u ", &message_len);
		message = new char [message_len + 1];
		
		read (fd, message, message_len);
		message[message_len] = 0;
		
		Failure *failure = NULL;
		Error *error = NULL;
		Unserialize (message, &failure, &error);
		delete[] message;
		
		if (failure != NULL)
		{
			output->fail (test, failure);
			delete failure;
		}
		
		if (error != NULL)
		{
			output->error (test, error);
			delete error;
		}
		
		if (failure == NULL && error == NULL)
		{
			output->pass (test);
		}
		
	}
	else
	{
		Error error = ProcessError(status);
		output->error(test, &error);
	}
}

bool RunChild (Test *test, int fd, Copper::List<Copper::Protector> protectors)
{
	ForkedTestRun test_run (fd, test);
	
	// TODO: protectors
	test_run.Run ();
	if (!test_run.got_error) { WriteMessage (fd, SerializePass ()); }
	return test_run.got_error;
}

}

namespace Copper {

void
ForkingTestRunner::RunTest (OutputHandler *output,
                            Test *test,
                            const List<Protector> &protectors)
{
	pid_t pid;
	int pipes[2];
	
	pipe (pipes);
	//fcntl (pipes[0], F_SETFL, O_NONBLOCK);
	pid = fork ();
	
	if (pid)
	{
		RunParent (test, pipes[0], pid, output);
		close (pipes[0]);
		close (pipes[1]);
	}
	
	else
	{
		bool got_error = RunChild (test, pipes[1], protectors);
		exit (got_error? 1 : 0);
	}
}

}
