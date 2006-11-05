/* formatters.hpp -- Convert various types to Copper::String
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef COPPER_UTIL_FORMATTERS_HPP
#define COPPER_UTIL_FORMATTERS_HPP

#include <copper/util/string.hpp>
#include <sstream>

namespace Copper {

template <class C>
String format(const C& c) {
  std::stringstream ss;
  ss << c;
  return String(ss.str().c_str());
}

template<>
String format<String>(const String& s) {
  return s;
}

} /* Namespace */

#endif /* COPPER_UTIL_FORMATTERS_HPP */
