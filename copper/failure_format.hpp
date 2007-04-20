/* failure_format.hpp -- Pretty formatting of failure messages
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_FAILURE_FORMAT_HPP
#define COPPER_FAILURE_FORMAT_HPP

#include <copper/util/formatters.hpp>

namespace Copper {
	template <class Value>
	String
	failure_format (const Value &value)
	{
		return format (value);
	}

	COPPER_EXPORT
	String
	failure_format(const char &v) throw ();

	COPPER_EXPORT
	String
	failure_format (const signed char &v) throw ();

	COPPER_EXPORT
	String
	failure_format (const unsigned char &v) throw ();

	COPPER_EXPORT
	String
	failure_format(const String &v) throw ();

	COPPER_EXPORT
	String
	failure_format (char *v) throw ();

	COPPER_EXPORT
	String
	failure_format (const char *v) throw ();

	template <class Value>
	String
	failure_format (const Value &value, const String &rest)
	{
		return failure_format (value) + " " + rest;
	}

	template <class A, class B>
	String
	failure_format (const A &a, const String& join, const B &b)
	{
		return failure_format (a) + " " + join + " " + failure_format (b);
	}
}

#endif /* COPPER_FAILURE_FORMAT_HPP */
