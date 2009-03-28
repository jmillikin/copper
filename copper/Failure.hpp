/* failure.hpp -- Records the failure of a test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/AssertionResult.hpp>
#include <copper/String.hpp>
#include <copper/export.hpp>

#ifndef COPPER_FAILURE_HPP
#define COPPER_FAILURE_HPP

namespace Copper
{
	class COPPER_EXPORT Failure
	{
	public:
		Failure (const String &text,
		         const String &message,
		         const String &file,
		         const unsigned int line);

		Failure (const char *text,
		         const char *message,
		         const char *file,
		         const unsigned int line);

		~Failure ();

		const String text;

		const String message;

		const String file;

		const unsigned int line;

	private:
		Failure &
		operator= (const Failure &);
	};
}

#endif /* COPPER_FAILURE_HPP */
