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

#include <lilac.h>

#include <copper/output_handler.hpp>
#include <copper/protector.hpp>
#include <copper/assertion.hpp>
#include "export.hpp"

namespace Copper {

EXPORT OutputHandler::OutputHandler() {
  // For now, do nothing
}

EXPORT OutputHandler::~OutputHandler() {}

LilacElement *
make_named (const char *name, int var)
{
	LilacAtom *atom = lilac_atom_new_integer (var);
	LilacNamedElement *named = lilac_named_element_new_atom (name, atom);
	return LILAC_ELEMENT (named);
}

LilacElement *
make_named (const char *name, const char* var)
{
	LilacAtom *atom = lilac_atom_new_string (var);
	LilacNamedElement *named = lilac_named_element_new_atom (name, atom);
	return LILAC_ELEMENT (named);
}

char *
serialize_failure (Assertion *failure)
{
	LilacObject *obj;
	LilacList *attrs = lilac_list_new ();
	char *message;

	lilac_list_append (attrs, make_named ("text", failure->text().c_str()));
	lilac_list_append (attrs, make_named ("line", failure->line()));
	lilac_list_append (attrs,
	                   make_named ("message",
	                               failure->failure_message().c_str()));

	obj = lilac_object_new ("failure", attrs);
	message = lilac_element_serialize (LILAC_ELEMENT (obj));

	lilac_element_free (LILAC_ELEMENT (obj));

	return message;
}

char *
serialize_error (Error *error)
{
	LilacObject *obj;
	LilacList *attrs = lilac_list_new ();
	char *message;

	lilac_list_append (attrs, make_named ("message",
	                                      error->message.c_str()));

	obj = lilac_object_new ("error", attrs);
	message = lilac_element_serialize (LILAC_ELEMENT (obj));

	lilac_element_free (LILAC_ELEMENT (obj));

	return message;
}

char *
serialize_pass ()
{
	return strdup ("(test (passed null))");
}

void
unserialize (const char *message, Assertion **failure, Error **error)
{
	LilacElement *element;
	LilacObject *obj;

	lilac_element_parse (message, &element);

	if (LILAC_IS_OBJECT (element))
	{
		String type;
		obj = LILAC_OBJECT (element);

		type = lilac_object_get_name (obj);

		if (type == "failure")
		{
			LilacList *attrs;
			LilacNamedElement *text_e, *line_e, *message_e;
			LilacAtom *text_a, *line_a, *message_a;
			const char *text, *message;
			unsigned int line;

			attrs = lilac_object_get_attributes (obj);
			text_e = LILAC_NAMED_ELEMENT (lilac_list_get_child (attrs, 0));
			line_e = LILAC_NAMED_ELEMENT (lilac_list_get_child (attrs, 1));
			message_e = LILAC_NAMED_ELEMENT (lilac_list_get_child (attrs, 2));

			text_a = lilac_named_element_get_atom (text_e);
			line_a = lilac_named_element_get_atom (line_e);
			message_a = lilac_named_element_get_atom (message_e);

			text = lilac_atom_get_string (text_a);
			line = lilac_atom_get_integer (line_a);
			message = lilac_atom_get_string (message_a);

			*failure = new Assertion(false, text, message, line);
		}

		else if (type == "error")
		{
			LilacList *attrs;
			LilacNamedElement *message_e;
			LilacAtom *message_a;
			const char *message;

			attrs = lilac_object_get_attributes (obj);

			message_e = LILAC_NAMED_ELEMENT (lilac_list_get_child (attrs, 0));
			message_a = lilac_named_element_get_atom (message_e);
			message = lilac_atom_get_string (message_a);

			*error = new Error(message);
		}
	}

	else
	{
		*error = new Error("Invalid message from child process");
	}

	lilac_element_free (element);
}

void
fork_test (Test *test, bool protect, Assertion **failure, Error **error)
{
	pid_t pid;
	int pipes[2];
	char buf[30];
	unsigned int message_len;
	char *message;

	pipe (pipes);

	pid = fork ();

	if (pid)
	{
		int status;
		waitpid (pid, &status, 0);

		if (WIFEXITED (status))
		{
			read (pipes[0], buf, 10);
			buf[10] = 0;

			sscanf (buf, "%u ", &message_len);
			message = new char [message_len + 1];

			read (pipes[0], message, message_len);
			message[message_len] = 0;

			unserialize (message, failure, error);

			delete message;
		}

		else
		{
			/* Something went wrong */
			*error = new Error("Child terminated early");
		}
	}

	else
	{
		if (protect)
			Protector::guard(test, failure, error);
		else
			test->run();

		if (*failure)
		{
			message = serialize_failure (*failure);
			delete *failure;
		}

		else if (*error)
		{
			message = serialize_error (*error);
			delete *error;
		}

		else
			message = serialize_pass ();

		message_len = strlen (message);
		sprintf (buf, "%-10u", message_len);
		write (pipes[1], buf, 10);
		write (pipes[1], message, message_len);
		free (message);

		exit (0);
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
