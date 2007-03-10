/* assertions.cpp - Available assertions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/assertions.hpp>
#include <copper/util/string.hpp>
#include "export.hpp"

// Overloads for equal()

EXPORT Copper::AssertionResult equal(const char* expected,
  const char* actual) throw () {

  Copper::String s_expected(expected), s_actual(actual);
  return equal(s_expected, s_actual);
}

EXPORT Copper::AssertionResult equal(const char* expected,
  char actual[]) throw () {

  Copper::String s_expected(expected), s_actual(actual);
  return equal(s_expected, s_actual);
}

EXPORT Copper::AssertionResult equal(char expected[],
  const char* actual) throw () {

  Copper::String s_expected(expected), s_actual(actual);
  return equal(s_expected, s_actual);
}

EXPORT Copper::AssertionResult equal(char expected[],
  char actual[]) throw () {

  Copper::String s_expected(expected), s_actual(actual);
  return equal(s_expected, s_actual);
}

// Overloads for unequal()

EXPORT Copper::AssertionResult unequal(const char* bad,
  const char* actual) throw () {

  Copper::String s_actual(actual), s_bad(bad);
  return unequal(s_bad, s_actual);
}

EXPORT Copper::AssertionResult unequal(const char* bad,
  char actual[]) throw () {

  Copper::String s_actual(actual), s_bad(bad);
  return unequal(s_bad, s_actual);
}

EXPORT Copper::AssertionResult unequal(char bad[],
  const char* actual) throw () {

  Copper::String s_actual(actual), s_bad(bad);
  return unequal(s_bad, s_actual);
}

EXPORT Copper::AssertionResult unequal(char bad[],
  char actual[]) throw () {

  Copper::String s_actual(actual), s_bad(bad);
  return unequal(s_bad, s_actual);
}
