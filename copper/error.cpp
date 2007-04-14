/* error.cpp -- Created when an execution error occurs
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/error.hpp>

namespace Copper
{
	Error::Error (const String &_message) throw ():
	              message (_message)
	{
	}

	Error::~Error () throw () 
	{
	}
}
