/* compat.hpp -- Compatibility header
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_COMPAT_HPP
#define COPPER_COMPAT_HPP

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

// If config.h doesn't define these, default to enabling everything
#ifndef HAVE_SSTREAM
#	define HAVE_SSTREAM 1
#endif

#ifndef HAVE_BOOLEAN
#	define HAVE_BOOLEAN 1
#endif

#ifndef HAVE_EXCEPTIONS
#	define HAVE_EXCEPTIONS 1
#endif

#ifdef __GNUC__
#	define COPPER_UNUSED __attribute__((__unused__))
#else
#	define COPPER_UNUSED
#endif

// For visual studio
#ifdef _MSC_VER
	// Disable warnings about ANSI C functions being deprecated
#	pragma warning (disable: 4996)
#endif /* _MSC_VER */

#endif /* COPPER_COMPAT_HPP */
