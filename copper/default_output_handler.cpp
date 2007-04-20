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
	/**
	 * Private implementation details of DefaultOutputHandler.
	 */
	class DefaultOutputHandlerPrivate
	{
	public:
		DefaultOutputHandlerPrivate (List<Test> tests):
		                             num_passed (0),
		                             num_failed (0),
		                             num_errors (0),
		                             protect (true),
		                             tests (tests)
		{
		}

		/** The number of tests that have passed. */
		unsigned int num_passed;

		/** The number of failed tests. */
		unsigned int num_failed;

		/** The number of tests that had errors. */
		unsigned int num_errors;

		/** Whether to protect running tests from runtime errors. */
		bool protect;

		/* A list of which tests to run. */
		List<Test> tests;
	};

	typedef DefaultOutputHandlerPrivate DOHP;

	/** @class DefaultOutputHandler
	 * This is a default implementation of an OutputHandler. It will
	 * output failures to the standard error stream.
	 */

	/** Default constructor */
	DefaultOutputHandler::DefaultOutputHandler (int &argc, char **&argv) throw ():
	                                            OutputHandler (),
	                                            priv (new DOHP (parse_test_args (argc, argv)))
	{
		// Allow exception catching to be toggled on or off at runtime
		for (int ii = 1; ii < argc; ii++)
		{
			if (strcmp (argv[ii], "--no-protection") == 0)
			{
				priv->protect = false;
				break;
			}	 
		}
	}

	/** Default destructor */
	DefaultOutputHandler::~DefaultOutputHandler () throw ()
	{
		delete priv;
	}

	/** Does nothing */
	void
	DefaultOutputHandler::begin (const Test *) throw ()
	{
	}

	/** Outputs nothing, but keeps track of how many tests passed. */
	void
	DefaultOutputHandler::pass (const Test *) throw ()
	{
		++priv->num_passed;
	}

	/**
	 * Outputs failures to the standard error stream. Also keeps track of
	 * how many tests failed.
	 * 
	 * @param test The test that failed.
	 * @param failure Details of the failed assertion.
	 */
	void
	DefaultOutputHandler::fail (const Test *test,
	                            const Failure *failure) throw ()
	{
		++priv->num_failed;

		fprintf(stderr,
		        "FAILURE in %s:%u:\n"
		        "%s.%s:\n"
		        "\t%s\n"
		        "\t%s\n\n",
		        test->file_name.c_str(), failure->line,
		        test->suite.c_str(), test->name.c_str(),
		        failure->text.c_str(),
		        failure->message.c_str());
	}

	/**
	 * Outputs errors to the standard error stream. Also keeps track of
	 * how many tests errored out.
	 * 
	 * @param test The test that failed.
	 * @param error The error that occurred.
	 */
	void
	DefaultOutputHandler::error (const Test *test,
	                             const Error *error) throw ()
	{
		++priv->num_errors;

		fprintf(stderr,
		        "ERROR in %s:\n"
		        "%s.%s:\n"
		        "\t%s\n\n",
		        test->file_name.c_str(),
		        test->suite.c_str(), test->name.c_str(),
		        error->message.c_str());
	}

	/**
	 * Run every test available.
	 * 
	 * @return The number of failures + the number of errors.
	 */
	int
	DefaultOutputHandler::run ()
	{
		// Reset statistics
		priv->num_passed = 0;
		priv->num_failed = 0;
		priv->num_errors = 0;

		// Store when the tests started
		time_t start_time;
		time (&start_time);

		// Run all tests
		run_tests (priv->tests, priv->protect);

		// Calculate running time
		time_t now;
		time (&now);

		// Print statistics
		printf ("%u tests passed\n"
		        "%u tests failed\n"
		        "%u errors\n",
		        priv->num_passed,
		        priv->num_failed,
		        priv->num_errors);

		// Print running time
		printf ("Completed in %g seconds\n",
		        difftime (now, start_time));

		return priv->num_failed + priv->num_errors;
	}
}
