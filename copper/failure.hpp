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
		/**
		 * Create a new failure record, to represent a failed assertion
		 * 
		 * @param text The code that this Assertion tests.
		 * @param message The human-readable failure message.
		 * @param file The name of the file containing the assertion.
		 * @param line The line the assertion is located on.
		 */
		Failure (const char *text,
		         const char *message,
		         const char *file,
		         const unsigned int line) throw ();
		/**
		 * Create a new failure record, to represent a failed assertion.
		 * This is an overloaded form, used to prevent unneeded copies
		 * of parameter data from String to char * and back.
		 * 
		 * @param text The code that this Assertion tests.
		 * @param message The human-readable failure message.
		 * @param file The name of the file containing the assertion.
		 * @param line The line the assertion is located on.
		 */
		Failure (const String &text,
		         const String &message,
		         const String &file,
		         const unsigned int line) throw ();

		/** Default destructor */
		~Failure () throw ();

		/** The code that this Assertion tests */
		const String text;

		/** The human-readable failure message */
		const String message;

		/** The name of the file containing the assertion */
		const String file;

		/** The line the assertion is located on */
		const unsigned int line;

	private:
		Failure &
		operator= (const Failure &) throw ();
	};
}

#endif /* COPPER_FAILURE_HPP */
