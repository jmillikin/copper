/* FuncAttrs.hpp -- Defines useful macros for various GCC function attributes
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */
 
#ifndef COPPER_FUNCATTRS_HPP
#define COPPER_FUNCATTRS_HPP

#if __GNUC__ >= 4
#	define COPPER_FUNCATTR_EXPORT __attribute__((visibility ("default")))
#	define COPPER_FUNCATTR_NULL_TERMINATED __attribute__((__sentinel__))
#else
#	define COPPER_FUNCATTR_EXPORT
#	define COPPER_FUNCATTR_NULL_TERMINATED
#endif

#ifdef __GNUC__
#	define COPPER_FUNCATTR_UNUSED __attribute__((__unused__))
#else
#	define COPPER_FUNCATTR_UNUSED
#endif

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 96)
#	define COPPER_FUNCATTR_MALLOC __attribute__((__malloc__))
#else
#	define COPPER_FUNCATTR_MALLOC
#endif

#endif
