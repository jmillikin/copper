/* failure.cpp -- Records the failure of a test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/Failure.hpp>

namespace Copper
{
	/** @class Failure
	 * @brief Stores information on a failed assertion.
	 */

	/** @var Failure::Text
	 * @brief The code that this Assertion tests.
	 */

	/** @var Failure::Message
	 * @brief The human-readable failure message.
	 */

	/** @var Failure::File
	 * @brief The name of the file containing the assertion.
	 */

	/** @var Failure::Line
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
	                  unsigned int line):

	                  Text (text),
	                  Message (message),
	                  File (file),
	                  Line (line)
	{
	}
}
