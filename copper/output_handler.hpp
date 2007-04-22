/* output_handler.hpp -- Base class for all output handlers
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_OUTPUT_HANDLER_HPP
#define COPPER_OUTPUT_HANDLER_HPP

#include <copper/test.hpp>
#include <copper/error.hpp>
#include <copper/export.hpp>
#include <copper/failure.hpp>
#include <copper/util/list.hpp>
#include <copper/util/string.hpp>

namespace Copper
{
	class COPPER_EXPORT OutputHandler
	{
	public:
		OutputHandler ();

		virtual
		~OutputHandler ();

		/**
		 * This function is called whenever a test is begun.
		 * 
		 * @param test The test that is about to run.
		 */
		virtual
		void
		begin (const Test *test) throw () = 0;

		/**
		 * This function is called whenever a test passes.
		 * 
		 * @param test The test that passed.
		 */
		virtual
		void
		pass (const Test *test) throw () = 0;

		/**
		 * This function is called whenever a test fails.
		 * 
		 * @param test The test that failed.
		 * @param failure Details of the failed assertion.
		 */
		virtual
		void
		fail (const Test *test, const Failure *failure)
			throw () = 0;

		/**
		 * This function is called whenever a test encounters an error
		 * while running.
		 * 
		 * @param test The test that failed.
		 * @param error The error that occurred.
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

		static
		List<Test> *
		parse_test_args (int argc, char **argv);

	protected:
		void
		run_test (Test *test, bool protect = true);

		void
		run_tests (const List<Test> *tests, bool protect = true);
	};
}

#endif /* COPPER_OUTPUT_HANDLER_HPP */
