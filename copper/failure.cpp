/* failure.cpp -- Records the failure of a test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "export.hpp"
#include "failure.hpp"

namespace Copper
{
	/** @class Failure
	 */


	/** @var Failure::text
	 * The code that this Assertion tests
	 */

	/** @var Failure::message
	 * The human-readable failure message
	 */

	/** @var Failure::file
	 * The name of the file containing the assertion
	 */

	/** @var Failure::line
	 * The line the assertion is located on
	 */

	/**
	 * Create a new failure record, to represent a failed assertion
	 * 
	 * @param text The code that this Assertion tests.
	 * @param message The human-readable failure message.
	 * @param file The name of the file containing the assertion.
	 * @param line The line the assertion is located on.
	 */
	EXPORT
	Failure::Failure (const char *text,
	                  const char *message,
	                  const char *file,
	                  const unsigned int line) throw ():

	                  text (text),
	                  message (message),
	                  file (file),
	                  line (line)
	{
	}

	/**
	 * Create a new failure record, to represent a failed assertion. This
	 * is an overloaded form, used to prevent unneeded copies of parameter
	 * data from String to char * and back.
	 * 
	 * @param text The code that this Assertion tests.
	 * @param message The human-readable failure message.
	 * @param file The name of the file containing the assertion.
	 * @param line The line the assertion is located on.
	 */
	EXPORT
	Failure::Failure (const String &text,
	                  const String &message,
	                  const String &file,
	                  const unsigned int line) throw ():

	                  text (text),
	                  message (message),
	                  file (file),
	                  line (line)
	{
	}

	/** Default destructor */
	EXPORT
	Failure::~Failure () throw ()
	{
	}
}
