/* failure.cpp -- Records the failure of a test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "failure.hpp"

namespace Copper
{
	/** @class Failure
	 * @brief Stores information on a failed assertion.
	 */

	/** @var Failure::text
	 * @brief The code that this Assertion tests.
	 */

	/** @var Failure::message
	 * @brief The human-readable failure message.
	 */

	/** @var Failure::file
	 * @brief The name of the file containing the assertion.
	 */

	/** @var Failure::line
	 * @brief The line the assertion is located on.
	 */

	/**
	 * @brief Create a new failure record.
	 * 
	 * @param text The code that was asserted.
	 * @param message The human-readable failure message.
	 * @param file The name of the file containing the assertion.
	 * @param line The line the assertion is located on.
	 */
	Failure::Failure (const String &text,
	                  const String &message,
	                  const String &file,
	                  const unsigned int line):

	                  text (text),
	                  message (message),
	                  file (file),
	                  line (line)
	{
	}

	/**
	 * @brief Create a new failure record.
	 * 
	 * @overload
	 * 
	 * @param text The code that was asserted.
	 * @param message The human-readable failure message.
	 * @param file The name of the file containing the assertion.
	 * @param line The line the assertion is located on.
	 */
	Failure::Failure (const char *text,
	                  const char *message,
	                  const char *file,
	                  const unsigned int line):

	                  text (text),
	                  message (message),
	                  file (file),
	                  line (line)
	{
	}

	/**
	 * @brief Default destructor
	 */
	Failure::~Failure ()
	{
	}
}
