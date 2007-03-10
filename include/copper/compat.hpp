/* compat.hpp -- Compatibility header
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_COMPAT_HPP
#define COPPER_COMPAT_HPP

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// For visual studio
#ifdef _MSC_VER
// Disable warnings about throw specifications
#pragma warning(disable: 4290)

// Disable warnings about ANSI C functions being deprecated
#pragma warning(disable: 4996)

#define HAVE_SSTREAM 1
#define HAVE_BOOLEAN 1
#define HAVE_EXCEPTIONS 1

#endif /* _MSC_VER */

#endif /* COPPER_COMPAT_HPP */
