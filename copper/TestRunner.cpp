/* test_runner.cpp -- Functions for safely and portably running a test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstring>

#include <copper/Error.hpp>
#include <copper/Failure.hpp>
#include <copper/Protector.hpp>
#include <copper/SafeException.hpp>
#include <copper/Test.hpp>
#include <copper/TestRunner.hpp>
#include <copper/TestStatus.hpp>

using Copper::String;
using Copper::Failure;
using Copper::Error;
using Copper::Test;

#if HAVE_FORK

#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <copper/Formatters.hpp>
using Copper::format;

struct FailureHandlerData
{
	int fd;
	Test *test;
};

Error *
process_error (int status);

void
write_message (int fd, const String &message);

void
fork_test (Test *test, bool protect, Failure **failure, Error **error);
#endif

class FailureException : public Copper::SafeException
{
public:
	FailureException (const Failure _failure):
	                  failure (_failure)
	{
	}

	const Failure failure;
};

void
on_thrown_failure (const Failure &failure, void *data)
{
	Test *test = (Test *) data;

	assert (test);
	test->tear_down ();
	throw FailureException (failure);
}

/**
 * Sent to set_failure_handler by all types of test execution. When the child
 * process forks from the parent, this function should call exit (1).
 */
void
on_failure (const Failure &failure, void *_data);

namespace Copper
{
	/**
	 * Execute a test. This function runs a test, usually in a restricted
	 * environment or in a different process for safety reasons.
	 * 
	 * @param test The test to run.
	 * @param protect Whether protectors should wrap the test's execution.
	 * @param failure This parameter will be set if a failure occurs.
	 * @param error This parameter will be set if an error occurs.
	 */
	void
	exec_test (Test *test,
	           bool protect,
	           Failure **failure,
	           Error **error)
	{
		if (protect)
		{
#if HAVE_FORK
			fork_test (test, protect, failure, error);
#else
			set_failure_handler (on_thrown_failure, test);
			try { *error = Copper::Protector::guard (test); }
			catch (const FailureException& e)
			{
				*failure = new Failure (e.failure);
			}
#endif
		}
		else
		{
			set_failure_handler (on_thrown_failure, test);
			
			try { test->run (); }
			catch (const FailureException& e)
			{
				*failure = new Failure (e.failure);
			}
		}
	}
}

#if HAVE_FORK

String
serialize_failure (const Failure *failure)
{
	/* 7:failure text line message */
	/* Example: "7:failure 6:0 == 1 2:10 18:values are unequal" */
	String line_str = format (failure->line),

	       line_len = format (line_str.size ()),
	       text_len = format (failure->text.size ()),
	       message_len = format (failure->message.size ());

	return String::build (10, "7:failure ",
	                      text_len.c_str (), ":",
	                      failure->text.c_str (),

	                      line_len.c_str (), ":",
	                      line_str.c_str (),

	                      message_len.c_str (), ":",
	                      failure->message.c_str ());
}

String
serialize_error (const Error *error)
{
	/* 5:error message */
	/* Example: "5:error 18:segmentation fault" */
	String message_len = format (error->message.size ());

	return String::build (4, "5:error ",
	                      message_len.c_str (), ":",
	                      error->message.c_str ());
}

String
serialize_pass ()
{
	return String::from_static ("6:passed");
}

String
parse_token (const char *message, const char **_next)
{
	char *next;
	unsigned int size;

	size = strtoul (message, &next, 10);
	next++; /* Skip the colon */

	/* Read the actual string */
	String token = String (next, size);
	next += size;

	/* Skip whitespace */
	while (isspace (next[0])) ++next;

	if (_next) *_next = next;
	return token;
}

void
unserialize (const char *c_message, Failure **failure, Error **error)
{
	if (strcmp (c_message, "6:passed") == 0)
		return;

	String type = parse_token (c_message, &c_message);

	if (type == "failure")
	{
		unsigned int line;

		String text = parse_token (c_message, &c_message),
		       line_str = parse_token (c_message, &c_message),
		       message = parse_token (c_message, &c_message);

		line = strtoul (line_str.c_str (), NULL, 10);

		*failure = new Failure (text, message, "", line);
	}

	else if (type == "error")
	{
		*error = new Error (parse_token (c_message, NULL));
	}
}


Error *
process_error (int status)
{
	if (WIFSIGNALED (status))
	{
		int sig = WTERMSIG (status);
		char *message;

#		if HAVE_STRSIGNAL
		message = strsignal (sig);
#		elif HAVE_SYS_SIGLIST
		message = sys_siglist[sig];
#		else
		message = "Unknown signal";
#		endif

		return new Error (message);
	}

	else
	{
		/* Something went wrong */
		return new Error ("Child terminated early");
	}
}

void
write_message (int fd, const String &message)
{
	char buf[30];

	sprintf (buf, "%-10u", message.size ());
	write (fd, buf, 10);
	write (fd, message.c_str (), message.size ());
}

void
on_failure (const Failure &failure, void *_data)
{
	FailureHandlerData *data = (FailureHandlerData *) _data;

	data->test->tear_down ();
	write_message (data->fd, serialize_failure (&failure));
	exit (1);
}

void
fork_test (Test *test, bool protect, Failure **failure, Error **error)
{
	pid_t pid;
	int pipes[2];
	char buf[30];

	pipe (pipes);

	fcntl (pipes[0], F_SETFL, O_NONBLOCK);

	pid = fork ();

	if (pid)
	{
		unsigned int message_len;
		char *message;
		int status;

		waitpid (pid, &status, 0);

		if (WIFEXITED (status))
		{
			status = read (pipes[0], buf, 10);

			if (status == -1)
			{
				*error = new Error (strerror (errno));
			}

			else
			{
				buf[10] = 0;

				sscanf (buf, "%u ", &message_len);
				message = new char [message_len + 1];

				read (pipes[0], message, message_len);
				message[message_len] = 0;

				unserialize (message, failure, error);

				delete[] message;
			}
		}

		else
		{
			*error = process_error (status);
		}

		close (pipes[0]);
		close (pipes[1]);
	}

	else
	{
		FailureHandlerData data = { pipes[1], test };
		set_failure_handler (on_failure, &data);

		if (protect)
			*error = Copper::Protector::guard (test);
		else
			test->run ();

		if (*error)
		{
			write_message (pipes[1], serialize_error (*error));
			delete *error;
			exit (1);
		}

		else
		{
			write_message (pipes[1], serialize_pass ());
			exit (0);
		}

	}
}
#else
#endif
