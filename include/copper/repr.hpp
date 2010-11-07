// Copyright (C) 2006-2010 John Millikin <jmillikin@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

#if HAVE_DISTINCT_BOOL
String repr(bool v);
#endif

String repr(char v);

String repr(const char *v);

String repr(const String &v);

String repr(signed char v);

String repr(unsigned char v);

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

#else // No sstream, only support standard C types + Copper::String

String repr(signed short v);

String repr(signed int v);

String repr(signed long v);

String repr(unsigned short v);

String repr(unsigned int v);

String repr(unsigned long v);

#if HAVE_DISTINCT_SIZE_T
String repr(std::size_t v);
#endif

String repr(float v);

String repr(double v);

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
