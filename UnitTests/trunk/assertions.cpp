/* assertions.cpp - Available assertions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "assertions.h"

void assert_func(const std::string& assertion, const UnitTests::AssertionResult& result,
  const unsigned int line) throw (UnitTests::FailureException) {

  if (!result.passed()) {
    throw UnitTests::FailureException(assertion, result.failure_message(), line);
  }
}

UnitTests::AssertionResult failed_func(const std::string& assertion,
  const UnitTests::AssertionResult& result) throw () {

  UnitTests::AssertionResult this_result;

  if (!result.passed()) {
    this_result.pass();
  }

  else {
    this_result.fail(("Unexpected sucess of assertion '" + assertion + "'").c_str());
  }

  return this_result;
}

UnitTests::AssertionResult equal(char const* result, char const* expected) throw () {
  std::string s_result = result, s_expected = expected;
  return equal(s_result, s_expected);
}

UnitTests::AssertionResult unequal(char const* bad, char const* result) throw () {
  std::string s_result = result, s_bad = bad;
  return unequal(s_bad, s_result);
}
