/* output_handler.cpp -- Outputs tests results to stdout and stderr
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <ctime>
#include <cstdio>
#include <cstring>
#include "default_output_handler.hpp"

using namespace std;

namespace Copper
{
	DefaultOutputHandler::DefaultOutputHandler (int &argc, char **&argv) throw ():
	                                            OutputHandler (),
	                                            num_passed (0),
	                                            num_failed (0),
	                                            num_errors (0),
	                                            protect (true),
	                                            tests (parse_test_args (argc, argv))
	{
		// Allow exception catching to be toggled on or off at runtime
		for (int ii = 1; ii < argc; ii++)
		{
			if (strcmp (argv[ii], "--no-protection") == 0)
			{
				protect = false;
				break;
			}	 
		}
	}

	DefaultOutputHandler::~DefaultOutputHandler () throw ()
	{
	}

	void
	DefaultOutputHandler::begin (const Test *) throw ()
	{
	}

	void
	DefaultOutputHandler::pass (const Test *) throw ()
	{
		++num_passed;
	}

	void
	DefaultOutputHandler::fail (const Test *test,
	                            const Failure *failure) throw ()
	{
		++num_failed;

		fprintf(stderr,
		        "FAILURE in %s:%u:\n"
		        "%s.%s:\n"
		        "\t%s\n"
		        "\t%s\n\n",
		        test->file_name.c_str(), failure->line,
		        test->suite->name.c_str(), test->name.c_str(),
		        failure->text.c_str(),
		        failure->message.c_str());
	}

	void
	DefaultOutputHandler::error (const Test *test,
	                             const Error *error) throw ()
	{
		++num_errors;

		fprintf(stderr,
		        "ERROR in %s:\n"
		        "%s.%s:\n"
		        "\t%s\n\n",
		        test->file_name.c_str(),
		        test->suite->name.c_str(), test->name.c_str(),
		        error->message.c_str());
	}

	int
	DefaultOutputHandler::run ()
	{
		// Reset statistics
		num_passed = 0;
		num_failed = 0;
		num_errors = 0;

		// Store when the tests started
		time_t start_time;
		time (&start_time);

		// Run all tests
		run_tests (tests, protect);

		// Calculate running time
		time_t now;
		time (&now);

		// Print statistics
		printf ("%u tests passed\n"
		        "%u tests failed\n"
		        "%u errors\n", num_passed, num_failed, num_errors);

		// Print running time
		printf ("Completed in %g seconds\n",
		        difftime (now, start_time));

		return num_failed + num_errors;
	}
}
