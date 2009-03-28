/* failure_format.hpp -- Pretty formatting of failure messages
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_FAILURE_FORMAT_HPP
#define COPPER_FAILURE_FORMAT_HPP

#include <copper/Formatters.hpp>
#if HAVE_STD_STRING
#	include <string>
#endif

namespace Copper {
	template <class Value>
	String
	failure_format (const Value &value)
	{
		return format (value);
	}

	COPPER_FUNCATTR_EXPORT
	String
	failure_format(const char &v);

	COPPER_FUNCATTR_EXPORT
	String
	failure_format (const signed char &v);

	COPPER_FUNCATTR_EXPORT
	String
	failure_format (const unsigned char &v);

	COPPER_FUNCATTR_EXPORT
	String
	failure_format(const String &v);

	COPPER_FUNCATTR_EXPORT
	String
	failure_format (char *v);

	COPPER_FUNCATTR_EXPORT
	String
	failure_format (const char *v);

#if HAVE_STD_STRING
	COPPER_FUNCATTR_EXPORT
	String
	failure_format (const std::string &v);
#endif

	template <class Value>
	String
	failure_format (const Value &value, const char *rest)
	{
		return String::Build (failure_format (value).CStr (),
		                      " ",
		                      rest, NULL);
	}

	template <class A, class B>
	String
	failure_format (const A &a, const char *join, const B &b)
	{
		return String::Build (failure_format (a).CStr (),
		                      " ",
		                      join,
		                      " ",
		                      failure_format (b).CStr (), NULL);
	}
}

#endif /* COPPER_FAILURE_FORMAT_HPP */
