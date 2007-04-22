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
	/** @class OutputHandler
	 * @brief Abstract class for output handlers.
	 * 
	 * An output handler decides which tests to run, and how to display
	 * the output to the user.
	 * 
	 * This class must be subclassed to provide different output formats.
	 */

	/**
	 * @brief Default constructor
	 */
	OutputHandler::OutputHandler ()
	{
	}

	/**
	 * @brief Default destructor
	 */
	OutputHandler::~OutputHandler ()
	{
	}

	/**
	 * @brief Parse commandline arguments into a list of tests.
	 * 
	 * Arguments may be in one of two forms: suite_name, or
	 * suite_name.test_name. In the first case, every test in the named
	 * suite will be added to the test list. In the second, only the
	 * single test will be added.
	 * 
	 * The parameters to main () should not be passed directly to this
	 * function, because they contain the executable name. Instead,
	 * pass argc-1 and argv+1.
	 * 
	 * @param argc The argument count.
	 * @param argv The arguments.
	 * 
	 * @return A list of tests that match the given arguments. This list
	 *         must be deleted when it is no longer needed.
	 */
	List<Test> *
	OutputHandler::parse_test_args (int argc, char **argv)
	{
		List<Test> *tests = new List<Test>;

		for (int ii = 0; ii < argc; ii++)
		{
			const char *name = argv[ii];
			const char *midpoint = strchr (name, '.');

			if (midpoint)
			{
				// This name includes a test name
				String suite_name (name, midpoint - name);
				String test_name (midpoint + 1);

				Test *test = Test::find (suite_name,
				                         test_name);
				if (test)
				{
					tests->append (test);
				}
			}

			else
			{
				// No test name, append everything in the suite
				tests->extend (Test::in_suite (name));
			}
		}

		if (!tests->size ())
			tests->extend (Test::all ());

		return tests;
	}

	/**
	 * @brief Run a single test.
	 * 
	 * This will try to run a test. begin () will be called before the
	 * test starts. After the test completes, one of error (), fail (),
	 * or pass () will be called with the proper arguments.
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
	 * @brief Run a list of tests.
	 * 
	 * @see run_test ()
	 * 
	 * @param tests The tests to run
	 * @param protect Whether to use Protectors to guard against
	 *                runtime errors.
	 */
	void
	OutputHandler::run_tests (const List<Test> *tests, bool protect)
	{
		const ListNode<Test> *node = tests->root ();
		while (node)
		{
			run_test (node->value, protect);
			node = node->next;
		}
	}
}
