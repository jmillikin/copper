/* repr.hpp -- String representations of tested types
 * Copyright (C) 2006-2010 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_REPR_HPP
#define COPPER_REPR_HPP

#include <copper/config.h>
#include <copper/String.hpp>

#if HAVE_SSTREAM
#	include <sstream>
#endif

#if HAVE_STD_STRING
#	include <string>
#endif

namespace Copper {

#if HAVE_BOOLEAN
String repr(const bool v);
#endif

String repr(const char v);

String repr(const char *v);

String repr(const String &v);

String repr(const signed char v);

String repr(const unsigned char v);

#if HAVE_STD_STRING
String repr(const std::string &v);
#endif

#if HAVE_SSTREAM

template <class C>
String repr(const C &v)
{
	std::stringstream ss;
	ss << v;
	return String (ss.str ().c_str ());
}

#else /* No sstream, only support standard C types + Copper::String */

String repr(const signed short v);

String repr(const signed int v);

String repr(const signed long v);

String repr(const unsigned short v);

String repr(const unsigned int v);

String repr(const unsigned long v);

String repr(const float v);

String repr(const double v);

#endif

// Used for assertion failure formatting
template <class Value>
String repr_expr(const Value value, const char *rest)
{
	return String::Build
		( repr(value).CStr()
		, " "
		, rest
		, NULL
		);
}

template <class A, class B>
String repr_expr(const A a, const char *join, const B b)
{
	return String::Build
		( repr(a).CStr()
		, " "
		, join
		, " "
		, repr(b).CStr()
		, NULL
		);
}

}

#endif
