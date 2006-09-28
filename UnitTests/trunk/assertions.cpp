/* assertions.cpp - Available assertions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "assertions.hpp"

UnitTests::AssertionResult equal(char const* expected, char const* actual)
  throw () {

  std::string s_expected = expected, s_actual = actual;
  return equal(s_expected, s_actual);
}

UnitTests::AssertionResult unequal(char const* bad, char const* actual)
  throw () {

  std::string s_actual = actual, s_bad = bad;
  return unequal(s_bad, s_actual);
}
