/* default_output_handler.hpp -- Outputs test results to stdout and stderr
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_DEFAULT_OUTPUT_HANDLER_HPP
#define COPPER_DEFAULT_OUTPUT_HANDLER_HPP

#include <copper/output_handler.hpp>

namespace Copper
{

	/**
	 * This is a default implementation of an OutputHandler. It will
	 * output failures to the standard error stream
	 */
	class DefaultOutputHandler : public OutputHandler
	{
	public:
		/** Default constructor */
		DefaultOutputHandler (int &argc, char **&argv) throw ();

		/** Default destructor */
		~DefaultOutputHandler () throw ();

		/** Does nothing */
		void begin (const Test *test) throw ();

		/**
		 * Outputs nothing, but keeps track of how many tests passed
		 * 
		 * @param test The test that passed
		 */
		void pass (const Test *test) throw ();

		/**
		 * Outputs failures to the standard error stream. Also keeps
		 * track of how many tests failed
		 * 
		 * @param test The test that failed
		 * @param assetion The assertion that caused the test to fail
		 */
		void
		fail(const Test *test, const Failure *assertion) throw ();

		/**
		 * Outputs errors to the standard error stream. Also keeps
		 * track of how many tests errored out
		 * 
		 * @param test The test that failed
		 * @param error The error that was thrown
		 */
		void
		error(const Test *test, const Error *error) throw ();

		/**
		 * Run every test available
		 * 
		 * @return The number of failures + the number of errors
		 */
		int
		run();

	protected:
		/** The number of tests that have passed */
		unsigned int num_passed;

		/** The number of failed tests */
		unsigned int num_failed;

		/** The number of tests that had errors */
		unsigned int num_errors;

		/** Whether to protect running tests from runtime errors */
		bool protect;

		/** Tests to run */
		List<Test> tests;
	};
}

#endif /* COPPER_DEFAULT_OUTPUT_HANDLER_HPP */
