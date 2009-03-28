/* default_output_handler.hpp -- Outputs test results to stdout and stderr
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_DEFAULT_OUTPUT_HANDLER_HPP
#define COPPER_DEFAULT_OUTPUT_HANDLER_HPP

#include <copper/export.hpp>
#include <copper/OutputHandler.hpp>

namespace Copper
{
	class COPPER_EXPORT DefaultOutputHandler : public OutputHandler
	{
	public:
		DefaultOutputHandler (int &argc, char **&argv);

		~DefaultOutputHandler ();

		void begin (const Test *test);

		void pass (const Test *test);

		void
		fail(const Test *test, const Failure *assertion);

		void
		error(const Test *test, const Error *error);

		int
		run();

	private:
		class DefaultOutputHandlerPrivate *priv;

		DefaultOutputHandler (const DefaultOutputHandler&);

		DefaultOutputHandler &
		operator= (const DefaultOutputHandler&);
	};
}

#endif /* COPPER_DEFAULT_OUTPUT_HANDLER_HPP */
