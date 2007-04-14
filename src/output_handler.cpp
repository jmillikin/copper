/* output_handler.cpp -- Base class for all output handlers
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstring>
#include <cstdlib>
#include <cstddef>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <copper/output_handler.hpp>
#include <copper/protector.hpp>
#include <copper/assertion.hpp>
#include <copper/test_status.hpp>
#include <copper/util/formatters.hpp>
#include "export.hpp"

namespace Copper {

EXPORT OutputHandler::OutputHandler() {
  // For now, do nothing
}

EXPORT OutputHandler::~OutputHandler() {}

String
serialize_failure (const Assertion *failure)
{
	/* 7:failure text line message */
	/* Example: "7:failure 6:0 == 1 2:10 18:values are unequal" */
	String line_str;
	String line_len, text_len, message_len;

	line_str = format (failure->line());

	line_len = format (line_str.size());
	text_len = format (failure->text().size());
	message_len = format (failure->failure_message().size());

	return String ("7:failure") + " " +
		text_len + ":" + failure->text() + " " +
		line_len + ":" + line_str + " " +
		message_len + ":" + failure->failure_message();
}

String
serialize_error (const Error *error)
{
	/* 5:error message */
	/* Example: "5:error 18:segmentation fault" */
	String message_len;

	message_len = format (error->message.size());

	return String ("5:error") + " " +
		message_len + ":" + error->message;
}

String
serialize_pass ()
{
	return String ("6:passed");
}

String
parse_token (const char *message, const char **_next)
{
	char *next;
	unsigned int size;
	String token;

	size = strtoul (message, &next, 10);
	next++; /* Skip the colon */

	/* Read the actual string */
	token = String (next, size);
	next += size;

	/* Skip whitespace */
	while (isspace (next[0])) ++next;

	if (_next) *_next = next;
	return token;
}

void
unserialize (const char *c_message, Assertion **failure, Error **error)
{
	String type = parse_token (c_message, &c_message);

	if (type == "failure")
	{
		String text, line_str, message;
		unsigned int line;

		text = parse_token (c_message, &c_message);
		line_str = parse_token (c_message, &c_message);
		message = parse_token (c_message, &c_message);

		line = strtoul (line_str.c_str(), NULL, 10);

		*failure = new Assertion (false, text, message, line);
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
		message = strsignal(sig);
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

void write_message (int fd, const String &message)
{
	char buf[30];

	sprintf (buf, "%-10u", message.size());
	write (fd, buf, 10);
	write (fd, message.c_str(), message.size());
}

void
on_failure (const Assertion& failure, void *data)
{
	int *fd = (int*) data;
	write_message (*fd, serialize_failure (&failure));
	exit (1);
}

void
fork_test (Test *test, bool protect, Assertion **failure, Error **error)
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

				delete message;
			}
		}

		else
		{
			*error = process_error (status);
		}
	}

	else
	{
		set_failure_handler (on_failure, &pipes[1]);

		if (protect)
			Protector::guard(test, error);
		else
			test->run();

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

EXPORT void
OutputHandler::run_test(Test* test, bool protect)
{
	begin (test);

	Assertion *failure = NULL;
	Error *test_error = NULL;

	fork_test (test, protect, &failure, &test_error);

	if (test_error)
	{
		error (test, test_error);
		delete test_error;
	}

	else if (failure)
	{
		fail (test, failure);
		delete failure;
	}

	else
	{
		pass (test);
	}
}

EXPORT void OutputHandler::run_tests(List<Test> tests, bool protect) {
  const ListNode<Test>* node = tests.root();
  while (node) {
    run_test(node->value, protect);
    node = node->next;
  }
}

Suite* find_suite(const char* name) {
  // Find all suites
  List<Suite> all = Suite::all_suites();

  const ListNode<Suite>* node = all.root();
  while (node) {
    Suite* suite = node->value;
    if (suite->name == name) {
      return suite;
    }
    node = node->next;
  }

  return NULL;
}

Test* find_test(const char* full_name) {
  // Separate the full name into suite name and test name
  std::size_t len = std::strlen(full_name);
  char* suite_name = new char[len+1];
  std::strcpy(suite_name, full_name);
  char* midpoint = std::strchr(suite_name, '.');
  char* test_name = midpoint + 1;
  *midpoint = 0;

  // Find the suite
  Suite* suite = find_suite(suite_name);

  if (!suite) {
    delete[] suite_name;
    return NULL;
  }

  // Find the test
  List<Test> suite_tests = suite->get_tests();
  const ListNode<Test>* node = suite_tests.root();
  while (node) {
    Test* test = node->value;
    if (test->name == test_name) {
      delete[] suite_name;
      return test;
    }
    node = node->next;
  }

  delete[] suite_name;
  return NULL;
}

EXPORT List<Test> OutputHandler::parse_test_args(int argc, char** argv) {
  List<Test> tests;

  for (int ii = 0; ii < argc; ii++) {
    const char* name = argv[ii];
    const char* midpoint = std::strchr(name, '.');

    if (midpoint) {
      // This name includes a test name
      Test* test = find_test(name);
      if (test) {
        tests.append(test);
      }
    }

    else {
      // No test name, append everything in the suite
      Suite* suite = find_suite(name);

      if (suite) {
        List<Test> suite_tests = suite->get_tests();
        const ListNode<Test>* node = suite_tests.root();
        while (node) {
          tests.append(node->value);
          node = node->next;
        }
      }
    }
  }

  if (tests.size()) {
    return tests;
  }

  else {
    return Test::all();
  }
}

} /* namespace */
