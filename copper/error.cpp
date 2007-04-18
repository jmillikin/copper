/* error.cpp -- Created when an execution error occurs
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "error.hpp"

namespace Copper
{
	/** @class Error
	 * This is used to indicate that something unexpected went wrong
	 * running a test.
	 */

	/** @var Error::message
	 * The error that occurred
	 */

	/**
	 * Default constructor
	 * 
	 * @param message The error string
	 */
	Error::Error (const String &message) throw ():
	              message (message)
	{
	}

	/** Default destructor */
	Error::~Error () throw () 
	{
	}
}
