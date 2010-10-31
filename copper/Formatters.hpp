/* formatters.hpp -- Convert various types to Copper::String
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_UTIL_FORMATTERS_HPP
#define COPPER_UTIL_FORMATTERS_HPP

#include <copper/String.hpp>
#include <copper/compat.hpp>
#include <copper/FuncAttrs.hpp>

#if HAVE_SSTREAM
#	include <sstream>
#endif /* HAVE_SSTREAM */

namespace Copper {

#if HAVE_BOOLEAN
	COPPER_FUNCATTR_EXPORT
	String
	format(const bool &v);
#endif

	COPPER_FUNCATTR_EXPORT
	String
	format(const char &v);

	COPPER_FUNCATTR_EXPORT
	String
	format (const signed char &v);

	COPPER_FUNCATTR_EXPORT
	String
	format (const unsigned char &v);

	COPPER_FUNCATTR_EXPORT
	String
	format(const String &v);

#if HAVE_SSTREAM

	template <class C>
	String
	format (const C &v)
	{
		std::stringstream ss;
		ss << v;
		return String (ss.str ().c_str ());
	}

#else /* No sstream, only support standard C types + Copper::String */

	COPPER_FUNCATTR_EXPORT
	String
	format (const signed short &v);

	COPPER_FUNCATTR_EXPORT
	String
	format (const unsigned short &v);

	COPPER_FUNCATTR_EXPORT
	String
	format (const signed int &v);

	COPPER_FUNCATTR_EXPORT
	String
	format (const unsigned int &v);

	COPPER_FUNCATTR_EXPORT
	String
	format (const signed long &v);

	COPPER_FUNCATTR_EXPORT
	String
	format (const unsigned long &v);

	COPPER_FUNCATTR_EXPORT
	String
	format (const float &v);

	COPPER_FUNCATTR_EXPORT
	String
	format (const double &v);

	COPPER_FUNCATTR_EXPORT
	String
	format (const char *v);
#endif /* HAVE_SSTREAM */
}

#endif /* COPPER_UTIL_FORMATTERS_HPP */
