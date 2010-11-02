/* formatters.hpp -- Convert various types to Copper::String
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_UTIL_FORMATTERS_HPP
#define COPPER_UTIL_FORMATTERS_HPP

#include <copper/config.h>
#include <copper/String.hpp>

#if HAVE_SSTREAM
#	include <sstream>
#endif

namespace Copper {

#if HAVE_BOOLEAN
	String
	format(const bool &v);
#endif

	String
	format(const char &v);

	String
	format (const signed char &v);

	String
	format (const unsigned char &v);

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

	String
	format (const signed short &v);

	String
	format (const unsigned short &v);

	String
	format (const signed int &v);

	String
	format (const unsigned int &v);

	String
	format (const signed long &v);

	String
	format (const unsigned long &v);

	String
	format (const float &v);

	String
	format (const double &v);

	String
	format (const char *v);
#endif /* HAVE_SSTREAM */
}

#endif /* COPPER_UTIL_FORMATTERS_HPP */
