/* output_handler.hpp -- Base class for all output handlers
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_OUTPUT_HANDLER_HPP
#define COPPER_OUTPUT_HANDLER_HPP

#include <copper/test.hpp>
#include <copper/error.hpp>
#include <copper/failure.hpp>
#include <copper/util/list.hpp>
#include <copper/util/string.hpp>

namespace Copper
{
	/**
	 * This class must be subclassed to provide different output formats
	 */
	class OutputHandler
	{
	public:
		/** Default constructor */
		OutputHandler ();

		/** Default destructor */
		virtual
		~OutputHandler ();

		/**
		 * This function is called whenever a test is begun.
		 * 
		 * @param test The test that is about to run
		 */
		virtual
		void
		begin (const Test *test) throw () = 0;

		/**
		 * This function is called whenever a test passes.
		 * 
		 * @param test The test that passed
		 */
		virtual
		void
		pass (const Test *test) throw () = 0;

		/**
		 * This function is called whenever a test fails.
		 * 
		 * @param test The test that failed
		 * @param assetion The assertion that caused the test to fail
		 */
		virtual
		void
		fail (const Test *test, const Failure *assertion)
			throw () = 0;

		/**
		 * This function is called whenever a test encounters an error
		 * while running.
		 * 
		 * @param test The test that failed
		 * @param error The error that was thrown
		 */
		virtual
		void
		error (const Test *test, const Error *error)
			throw () = 0;

		/**
		 * Run this output handler. The simplest implementations
		 * will run every test, the more complex ones may allow
		 * selection of which tests to run.
		 * 
		 * @return Should be 0 if all tests passed, otherwise up to
		 *         the implementation.
		 */
		virtual
		int
		run () = 0;

		/**
		 * Get a list of tests to run, by parsing commandline arguments
		 * 
		 * @param argc The argument count
		 * @param argv The arguments
		 * 
		 * @return A list of tests that match the given arguments
		 */
		static
		List<Test>
		parse_test_args (int argc, char **argv);

	protected:
		/**
		 * Run a single test. This function automatically manages
		 * Protectors and exception handling.
		 * 
		 * @param test The test to run
		 * @param protect Whether to use Protectors to guard against
		 *                runtime errors.
		 */
		void
		run_test (Test *test, bool protect = true);

		/**
		 * Run a many tests. This function automatically manages
		 * Protectors and exception handling.
		 * 
		 * @param tests The tests to run
		 * @param protect Whether to use Protectors to guard against
		 *                runtime errors.
		 */
		void
		run_tests (List<Test> tests, bool protect = true);
	};
}

#endif /* COPPER_OUTPUT_HANDLER_HPP */
