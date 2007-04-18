/* failure.hpp -- Records the failure of a test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/util/string.hpp>
#include <copper/assertion_result.hpp>

#ifndef COPPER_FAILURE_HPP
#define COPPER_FAILURE_HPP

namespace Copper
{
	class Failure
	{
	public:
		Failure (const char *text,
		         const char *message,
		         const char *file,
		         const unsigned int line) throw ();

		Failure (const String &text,
		         const String &message,
		         const String &file,
		         const unsigned int line) throw ();

		~Failure () throw ();

		const String text;

		const String message;

		const String file;

		const unsigned int line;

	private:
		Failure &
		operator= (const Failure &) throw ();
	};
}

#endif /* COPPER_FAILURE_HPP */
