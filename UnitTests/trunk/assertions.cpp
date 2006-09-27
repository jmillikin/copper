/* assertions.cpp - Available assertions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "assertions.h"

UnitTests::AssertionResult equal(char const* result, char const* expected) throw () {
  std::string s_result = result, s_expected = expected;
  return equal(s_result, s_expected);
}

UnitTests::AssertionResult unequal(char const* bad, char const* result) throw () {
  std::string s_result = result, s_bad = bad;
  return unequal(s_bad, s_result);
}
