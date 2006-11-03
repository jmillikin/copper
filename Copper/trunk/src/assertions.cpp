/* assertions.cpp - Available assertions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper/assertions.hpp>
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

// Overloads for equal()

EXPORT Copper::AssertionResult equal(const char* expected,
  const char* actual) throw () {

  MiniString s_expected(expected), s_actual(actual);
  return equal(s_expected, s_actual);
}

EXPORT Copper::AssertionResult equal(const char* expected,
  char actual[]) throw () {

  MiniString s_expected(expected), s_actual(actual);
  return equal(s_expected, s_actual);
}

EXPORT Copper::AssertionResult equal(char expected[],
  const char* actual) throw () {

  MiniString s_expected(expected), s_actual(actual);
  return equal(s_expected, s_actual);
}

EXPORT Copper::AssertionResult equal(char expected[],
  char actual[]) throw () {

  MiniString s_expected(expected), s_actual(actual);
  return equal(s_expected, s_actual);
}

// Overloads for unequal()

EXPORT Copper::AssertionResult unequal(const char* bad,
  const char* actual) throw () {

  MiniString s_actual(actual), s_bad(bad);
  return unequal(s_bad, s_actual);
}

EXPORT Copper::AssertionResult unequal(const char* bad,
  char actual[]) throw () {

  MiniString s_actual(actual), s_bad(bad);
  return unequal(s_bad, s_actual);
}

EXPORT Copper::AssertionResult unequal(char bad[],
  const char* actual) throw () {

  MiniString s_actual(actual), s_bad(bad);
  return unequal(s_bad, s_actual);
}

EXPORT Copper::AssertionResult unequal(char bad[],
  char actual[]) throw () {

  MiniString s_actual(actual), s_bad(bad);
  return unequal(s_bad, s_actual);
}
