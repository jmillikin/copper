/* output_handler.cpp -- Base class for all output handlers
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstring>
#include <cstdlib>
#include <cstddef>

#include "output_handler.hpp"
#include "test_runner.hpp"

using namespace std;

namespace Copper
{
	Suite *
	find_suite (const String &name);

	Test *
	find_test (const char *full_name);

	/** @class OutputHandler
	 * This class must be subclassed to provide different output formats.
	 */

	/** Default constructor */
	OutputHandler::OutputHandler ()
	{
	}

	/** Default destructor */
	OutputHandler::~OutputHandler ()
	{
	}

	/**
	 * Get a list of tests to run, by parsing commandline arguments.
	 * 
	 * @param argc The argument count.
	 * @param argv The arguments.
	 * 
	 * @return A list of tests that match the given arguments.
	 */
	List<Test>
	OutputHandler::parse_test_args (int argc, char **argv)
	{
		List<Test> tests;

		for (int ii = 0; ii < argc; ii++)
		{
			const char *name = argv[ii];
			const char *midpoint = strchr (name, '.');

			if (midpoint)
			{
				// This name includes a test name
				Test *test = find_test (name);
				if (test)
				{
					tests.append (test);
				}
			}

			else
			{
				// No test name, append everything in the suite
				Suite *suite = find_suite (name);

				if (suite)
				{
					tests.extend (suite->get_tests ());
				}
			}
		}

		if (tests.size ())
			return tests;

		else
			return Test::all ();
	}

	/**
	 * Run a single test. This function automatically manages Protectors
	 * and exception handling.
	 * 
	 * @param test The test to run.
	 * @param protect Whether to use Protectors to guard against runtime
	 *                errors.
	 */
	void
	OutputHandler::run_test (Test *test, bool protect)
	{
		begin (test);

		Failure *failure = NULL;
		Error *test_error = NULL;

		exec_test (test, protect, &failure, &test_error);

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

	/**
	 * Run a many tests. This function automatically manages
	 * Protectors and exception handling.
	 * 
	 * @param tests The tests to run
	 * @param protect Whether to use Protectors to guard against
	 *                runtime errors.
	 */
	void
	OutputHandler::run_tests (List<Test> tests, bool protect)
	{
		const ListNode<Test> *node = tests.root ();
		while (node)
		{
			run_test (node->value, protect);
			node = node->next;
		}
	}

	Suite *
	find_suite (const String &name)
	{
		// Find all suites
		List<Suite> all = Suite::all_suites ();

		const ListNode<Suite> *node = all.root ();
		while (node)
		{
			Suite *suite = node->value;
			if (suite->name == name)
			{
				return suite;
			}
			node = node->next;
		}

		return NULL;
	}

	Test *
	find_test (const char *full_name)
	{
		// Separate the full name into suite name and test name
		char *midpoint = strchr (full_name, '.');
		String suite_name (full_name, midpoint - full_name);
		String test_name (midpoint + 1);

		// Find the suite
		Suite *suite = find_suite (suite_name);

		if (!suite)
		{
			return NULL;
		}

		// Find the test
		List<Test> suite_tests = suite->get_tests ();
		const ListNode<Test> *node = suite_tests.root ();
		while (node)
		{
			Test *test = node->value;
			if (test->name == test_name)
			{
				return test;
			}
			node = node->next;
		}

		return NULL;
	}
}
