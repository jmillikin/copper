/* export.hpp -- Defines EXPORT macro
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#if __GNUC__ >= 4
	#define EXPORT __attribute__((visibility ("default")))
#else
	#define EXPORT
#endif
