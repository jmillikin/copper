/* formatters.hpp -- Convert various types to Copper::String
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef COPPER_UTIL_FORMATTERS_HPP
#define COPPER_UTIL_FORMATTERS_HPP

#include <copper/util/string.hpp>
#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include <cstdio>
#include <climits>
#endif

namespace Copper {

#ifdef HAVE_SSTREAM

template <class C>
String format(const C& v) throw () {
  std::stringstream ss;
  ss << v;
  return String(ss.str().c_str());
}

template<>
String format<String>(const String& v) throw () {
  return v;
}

#else /* No sstream, only support standard C types + Copper::String */

String format(const char& v) throw () {
  char buffer[2];
  std::sprintf(buffer, "%c", v);
  return String(buffer);
}

String format(const signed char& v) throw () {
  char buffer[2];
  std::sprintf(buffer, "%c", v);
  return String(buffer);
}

String format(const unsigned char& v) throw () {
  char buffer[2];
  std::sprintf(buffer, "%c", v);
  return String(buffer);
}

String format(const signed short& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%hd", v);
  return String(buffer);
}

String format(const unsigned short& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%hu", v);
  return String(buffer);
}

String format(const signed int& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%d", v);
  return String(buffer);
}

String format(const unsigned int& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%u", v);
  return String(buffer);
}

String format(const signed long& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%ld", v);
  return String(buffer);
}

String format(const unsigned long& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%lu", v);
  return String(buffer);
}

/* FIXME I'm pretty sure this will break for weird values */
String format(const float& v) throw () {
  char buffer[100]; /* FIXME: enough? */
  std::sprintf(buffer, "%g", v);
  return String(buffer);
}

/* FIXME, see format(float) */
String format(const double& v) throw () {
  return format(static_cast<float>(v));
}

String format(const String& v) throw () {
  return v;
}

#endif /* HAVE_SSTREAM */

} /* Namespace */

#endif /* COPPER_UTIL_FORMATTERS_HPP */
