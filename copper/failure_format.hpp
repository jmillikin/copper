/* failure_format.hpp -- Pretty formatting of failure messages
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_FAILURE_FORMAT_HPP
#define COPPER_FAILURE_FORMAT_HPP

#include <copper/util/formatters.hpp>
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

	COPPER_EXPORT
	String
	failure_format(const char &v);

	COPPER_EXPORT
	String
	failure_format (const signed char &v);

	COPPER_EXPORT
	String
	failure_format (const unsigned char &v);

	COPPER_EXPORT
	String
	failure_format(const String &v);

	COPPER_EXPORT
	String
	failure_format (char *v);

	COPPER_EXPORT
	String
	failure_format (const char *v);

#if HAVE_STD_STRING
	COPPER_EXPORT
	String
	failure_format (const std::string &v);
#endif

	template <class Value>
	String
	failure_format (const Value &value, const char *rest)
	{
		return String::build (3,
		                      failure_format (value).c_str (),
		                      " ",
		                      rest);
	}

	template <class A, class B>
	String
	failure_format (const A &a, const char *join, const B &b)
	{
		return String::build (5,
		                      failure_format (a).c_str (),
		                      " ",
		                      join,
		                      " ",
		                      failure_format (b).c_str ());
	}
}

#endif /* COPPER_FAILURE_FORMAT_HPP */
