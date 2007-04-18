/* default_output_handler.hpp -- Outputs test results to stdout and stderr
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_DEFAULT_OUTPUT_HANDLER_HPP
#define COPPER_DEFAULT_OUTPUT_HANDLER_HPP

#include <copper/export.hpp>
#include <copper/output_handler.hpp>

namespace Copper
{
	class COPPER_EXPORT DefaultOutputHandler : public OutputHandler
	{
	public:
		DefaultOutputHandler (int &argc, char **&argv) throw ();

		~DefaultOutputHandler () throw ();

		void begin (const Test *test) throw ();

		void pass (const Test *test) throw ();

		void
		fail(const Test *test, const Failure *assertion) throw ();

		void
		error(const Test *test, const Error *error) throw ();

		int
		run();

	protected:
		unsigned int num_passed;
		unsigned int num_failed;
		unsigned int num_errors;

		bool protect;

		List<Test> tests;
	};
}

#endif /* COPPER_DEFAULT_OUTPUT_HANDLER_HPP */
