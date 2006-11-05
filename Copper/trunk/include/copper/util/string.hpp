/* string.hpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef COPPER_UTIL_STRING_HPP
#define COPPER_UTIL_STRING_HPP

#include <cstddef>

namespace Copper {

class String {
public:
  String(const char* string = "") throw ();

  String(const String& other) throw ();

  ~String() throw ();

  const String& operator=(const String& other) throw ();

  bool operator==(const String& other) const throw ();

  String operator+(const String& other) const throw ();

  std::size_t size() const throw ();

  const char* c_str() const throw ();

protected:
  char* str;
};

bool operator==(const char* a, const String& b) throw ();

} /* Namespace */

#endif /* COPPER_UTIL_STRING_HPP */
