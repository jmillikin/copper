/* assertions.cpp - Available assertions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "assertions.hpp"
#include "export.hpp"

/** A simple class for string comparisons */
class MiniString {
  friend std::ostream& operator<<(std::ostream& out, const MiniString& str)
    throw ();
public:
  MiniString(const char* _str) throw ():
    str(_str) {}

  bool operator==(const MiniString& other) const throw () {
    return strcmp(str, other.str) == 0;
  }

  const char* str;
};

std::ostream& operator<<(std::ostream& out, const MiniString& str) throw () {
  out << str.str;
  return out;
}

EXPORT Copper::AssertionResult equal(char const* expected,
  char const* actual) throw () {

  MiniString s_expected(expected), s_actual(actual);
  return equal(s_expected, s_actual);
}

EXPORT Copper::AssertionResult unequal(char const* bad,
  char const* actual) throw () {

  MiniString s_actual(actual), s_bad(bad);
  return unequal(s_bad, s_actual);
}
