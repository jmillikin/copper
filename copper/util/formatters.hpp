/* formatters.hpp -- Convert various types to Copper::String
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_UTIL_FORMATTERS_HPP
#define COPPER_UTIL_FORMATTERS_HPP

#include <copper/compat.hpp>
#include <copper/export.hpp>
#include <copper/util/string.hpp>

#if HAVE_SSTREAM
#	include <sstream>
#endif /* HAVE_SSTREAM */

namespace Copper {

#if HAVE_BOOLEAN
	COPPER_EXPORT
	String
	format(const bool &v) throw ();
#endif

	COPPER_EXPORT
	String
	format(const char &v) throw ();

	COPPER_EXPORT
	String
	format (const signed char &v) throw ();

	COPPER_EXPORT
	String
	format (const unsigned char &v) throw ();

	COPPER_EXPORT
	String
	format(const String &v) throw ();

#if HAVE_SSTREAM

	template <class C>
	String
	format (const C &v) throw ()
	{
		std::stringstream ss;
		ss << v;
		return String (ss.str ().c_str ());
	}

#else /* No sstream, only support standard C types + Copper::String */

	COPPER_EXPORT
	String
	format (const signed short &v) throw ();

	COPPER_EXPORT
	String
	format (const unsigned short &v) throw ();

	COPPER_EXPORT
	String
	format (const signed int &v) throw ();

	COPPER_EXPORT
	String
	format (const unsigned int &v) throw ();

	COPPER_EXPORT
	String
	format (const signed long &v) throw ();

	COPPER_EXPORT
	String
	format (const unsigned long &v) throw ();

	COPPER_EXPORT
	String
	format (const float &v) throw ();

	COPPER_EXPORT
	String
	format (const double &v) throw ();

	COPPER_EXPORT
	String
	format (const char *v) throw ();
#endif /* HAVE_SSTREAM */

	template <class Value>
	String
	error_format (const Value &value)
	{
		return format (value);
	}

	COPPER_EXPORT
	String
	error_format(const char &v) throw ();

	COPPER_EXPORT
	String
	error_format (const signed char &v) throw ();

	COPPER_EXPORT
	String
	error_format (const unsigned char &v) throw ();

	COPPER_EXPORT
	String
	error_format(const String &v) throw ();

	COPPER_EXPORT
	String
	error_format (char *v) throw ();

	COPPER_EXPORT
	String
	error_format (const char *v) throw ();

	template <class Value>
	String
	error_format (const Value &value, const String &rest)
	{
		return error_format (value) + " " + rest;
	}

	template <class A, class B>
	String
	error_format (const A &a, const String& join, const B &b)
	{
		return error_format (a) + " " + join + " " + error_format (b);
	}
}

#endif /* COPPER_UTIL_FORMATTERS_HPP */
