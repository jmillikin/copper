/* formatters.hpp -- Convert various types to Copper::String
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_UTIL_FORMATTERS_HPP
#define COPPER_UTIL_FORMATTERS_HPP

#include <copper/util/string.hpp>
#include <copper/compat.hpp>

#if HAVE_SSTREAM
#include <sstream>
#else
#include <cstdio>
#include <climits>
#endif /* HAVE_SSTREAM */

namespace Copper {

#if HAVE_SSTREAM

template <class C>
String format(const C& v) throw () {
  std::stringstream ss;
  ss << v;
  return String(ss.str().c_str());
}

#if HAVE_BOOLEAN
template<>
String format<bool>(const bool& v) throw ();
#endif

template<>
String format<char>(const char& v) throw ();

template<>
String format<String>(const String& v) throw ();

#else /* No sstream, only support standard C types + Copper::String */

#if HAVE_BOOLEAN
String format(const bool& v) throw ();
#endif

String format(const char& v) throw ();

String format(const signed char& v) throw ();

String format(const unsigned char& v) throw ();

String format(const signed short& v) throw ();

String format(const unsigned short& v) throw ();

String format(const signed int& v) throw ();

String format(const unsigned int& v) throw ();

String format(const signed long& v) throw ();

String format(const unsigned long& v) throw ();

/* FIXME I'm pretty sure this will break for weird values */
String format(const float& v) throw ();

/* FIXME, see format(float) */
String format(const double& v) throw ();

String format(const char* v) throw ();

String format(const String& v) throw ();

#endif /* HAVE_SSTREAM */

} /* Namespace */

#endif /* COPPER_UTIL_FORMATTERS_HPP */
