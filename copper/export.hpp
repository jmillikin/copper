/* export.hpp -- Defines COPPER_EXPORT macro
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#if __GNUC__ >= 4
#	define COPPER_EXPORT __attribute__((visibility ("default")))
#else
#	define COPPER_EXPORT
#endif
