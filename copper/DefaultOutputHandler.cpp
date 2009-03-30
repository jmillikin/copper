/* output_handler.cpp -- Outputs tests results to stdout and stderr
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstdio>
#include <cstring>

#include <copper/DefaultOutputHandler.hpp>

using namespace std;

namespace Copper
{
	/**
	 * @brief Private implementation details of DefaultOutputHandler.
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

		/**
		 * @brief The number of tests that have passed.
		 */
		unsigned int num_passed;

		/**
		 * @brief The number of failed tests.
		 */
		unsigned int num_failed;

		/**
		 * @brief The number of tests that had errors.
		 */
		unsigned int num_errors;

		/**
		 * @brief Whether to protect running tests from runtime errors.
		 */
		bool protect;

		/*
		 * @brief A list of which tests to run.
		 */
		List<Test> tests;
	};

	typedef DefaultOutputHandlerPrivate DOHP;

	/** @class DefaultOutputHandler
	 * @brief Uses C's standard input/output library for printing
	 *        execution information.
	 * 
	 * This class also serves as a useful example of how to create a
	 * simple output handler.
	 */

	/**
	 * @brief Default constructor
	 * 
	 * @param argc The argument count.
	 * @param argv The arguments.
	 */
	DefaultOutputHandler::DefaultOutputHandler (int &argc, char **&argv):
	                                            OutputHandler ()
	{
		priv = new DOHP (parse_test_args (argc - 1, argv + 1));

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

	/**
	 * @brief Default destructor
	 */
	DefaultOutputHandler::~DefaultOutputHandler ()
	{
		delete priv;
	}

	/**
	 * @brief Does nothing
	 */
	void
	DefaultOutputHandler::begin (const Test *)
	{
	}

	/**
	 * @brief Output nothing.
	 * 
	 * Also keeps track of how many tests passed.
	 */
	void
	DefaultOutputHandler::pass (const Test *)
	{
		++priv->num_passed;
	}

	/**
	 * @brief Output failures to the standard error stream.
	 * 
	 * Also keeps track of how many tests failed.
	 * 
	 * @param test The test that failed.
	 * @param failure Details of the failed assertion.
	 */
	void
	DefaultOutputHandler::fail (const Test *test,
	                            const Failure *failure)
	{
		++priv->num_failed;

		fprintf(stderr,
		        "FAILURE in %s:%u:\n"
		        "%s.%s:\n"
		        "\t%s\n"
		        "\t%s\n\n",
		        test->FileName.CStr(), failure->Line,
		        test->Suite.CStr(), test->Name.CStr(),
		        failure->Text.CStr(),
		        failure->Message.CStr());
	}

	/**
	 * @brief Output errors to the standard error stream.
	 * 
	 * Also keeps track of how many tests errored out.
	 * 
	 * @param test The test that failed.
	 * @param error The error that occurred.
	 */
	void
	DefaultOutputHandler::error (const Test *test,
	                             const Error *error)
	{
		++priv->num_errors;

		fprintf(stderr,
		        "ERROR in %s:\n"
		        "%s.%s:\n"
		        "\t%s\n\n",
		        test->FileName.CStr(),
		        test->Suite.CStr(), test->Name.CStr(),
		        error->Message.CStr());
	}

	/**
	 * @brief Run every test available.
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

		// Run all tests
		run_tests (priv->tests, priv->protect);

		// Print statistics
		printf ("%u tests passed\n"
		        "%u tests failed\n"
		        "%u errors\n",
		        priv->num_passed,
		        priv->num_failed,
		        priv->num_errors);
		
		if ((priv->num_failed + priv->num_errors) > 0) { return 1; }
		return 0;
	}
}
