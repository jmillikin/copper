/* error.cpp -- Created when an execution error occurs
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "error.hpp"

namespace Copper
{
	/** @class Error
	 * @brief Stores information on an unexpected error.
	 * 
	 * This is used to indicate that something unexpected went wrong
	 * running a test. Errors should only be used for problems that
	 * would not be expected.
	 */

	/** @var Error::message
	 * @brief The error that occurred.
	 */

	/**
	 * @brief Initialize a new error.
	 * 
	 * @param message The error string.
	 */
	Error::Error (const String &message) throw ():
	              message (message)
	{
	}

	/**
	 * @brief Default, empty destructor
	 */
	Error::~Error () throw ()
	{
	}
}
