/* safe_exception.hpp -- An exception allowed to pass through protectors
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_SAFE_EXCEPTION_HPP
#define COPPER_SAFE_EXCEPTION_HPP

namespace Copper
{
	/**
	 * @brief Used for bypassing the exception protector.
	 * 
	 * This is an empty base class, which can be subclassed to create a
	 * class which will be thrown through the exception protector. For
	 * internal use of Copper only.
	 */
	class SafeException
	{
		/* Empty, subclass it */
	};
}

#endif /* COPPER_SAFE_EXCEPTION_HPP */

