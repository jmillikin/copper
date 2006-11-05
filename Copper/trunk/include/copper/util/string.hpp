/* list.hpp -- Simple linked list to avoid dependency on std::list
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef COPPER_UTIL_STRING_HPP
#define COPPER_UTIL_STRING_HPP

namespace Copper {

class String {
public:
  String(const char* string = "") throw ();

  String(const String& other) throw ();

  ~String() throw ();

  String& operator=(const String& other) const throw ();

  bool operator==(const String& other) const throw ();

  String operator+(const String& other) const throw ();

  size_t size() const throw ();

  const char* c_str() const throw ();

protected:
  char* str;
};

} /* Namespace */

#endif /* COPPER_UTIL_STRING_HPP */
