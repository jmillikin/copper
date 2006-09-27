/* assertions.h - Available assertions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef ASSERTIONS_H
#define ASSERTIONS_H

// For formatting error strings
#include <sstream>

#include "failure_exception.h"
#include "assertion_result.h"

// Disable warnings about throw specifications in VS 2003
#ifdef _MSC_VER
#pragma warning(disable: 4290)
#endif

/* Block any macro shenanigans from the standard library */
#ifdef assert
#undef assert
#endif

void assert_func(const std::string& assertion, const UnitTests::AssertionResult& result,
  const unsigned int line) throw (UnitTests::FailureException);

UnitTests::AssertionResult failed_func(const std::string& assertion,
  const UnitTests::AssertionResult& result) throw ();

/**
  Assert two values are equal

  @param result The value which should be tested against the expected value
  @param expected The expected value of this assertion

  @return An AssertionResult
*/
template <class T, class U>
UnitTests::AssertionResult equal(const T& result, const U& expected)
  throw () {

  UnitTests::AssertionResult cmp_result;
  if (result != expected) {
    std::stringstream ss;
    ss << "Unequal values: expected '" << expected
      << "', got '" << result << "'";
    cmp_result.fail(ss.str().c_str());
  }
  else {
    cmp_result.pass();
  }
  return cmp_result;
}

/**
  An overloaded form of equal(), used for character strings. This transforms
  the char*s into std::strings

  @param result The value which should be tested against the expected value
  @param expected The expected value of this assertion

  @return An AssertionResult
*/
UnitTests::AssertionResult equal(char const* result, char const* expected) throw ();

/**
  Check that the two values are nearly equal within a certain delta

  @param result The value which should be tested against the expected value
  @param expected The expected value of this assertion
  @param delta The allowable difference between the expected and actual
  values

  @return An AssertionResult
*/
template <class T>
UnitTests::AssertionResult equal_within(const T& result, const T& expected,
  const T& delta) throw () {

  UnitTests::AssertionResult cmp_result;
  if ((result < expected - delta) || (result > expected + delta)) {
    std::stringstream ss;
    ss << "Result '" << result << "' is not within '" << delta << "' of '"
        << expected << "'";
    cmp_result.fail(ss.str().c_str());
  }
  else {
    cmp_result.pass();
  }
  return cmp_result;
}

/**
  Assert two values are unequal

  @param bad Something that #actual should not be
  @param result The value which should be tested against the expected value

  @return An AssertionResult
*/
template <class T, class U>
UnitTests::AssertionResult unequal(const T& bad, const U& result) throw () {

  UnitTests::AssertionResult cmp_result;
  if (result == bad) {
    std::stringstream ss;
    ss << "'" << result << "' is equal to '" << bad << "'";
    cmp_result.fail(ss.str().c_str());
  }
  else {
    cmp_result.pass();
  }
  return cmp_result;
}

/**
  An overloaded form of unequal(), used for character strings. This transforms
  the char*s into std::strings

  @param bad Something that #actual should not be
  @param result The value which should be tested against the expected value

  @return An AssertionResult
*/
UnitTests::AssertionResult unequal(char const* bad, char const* result) throw ();

/**
  Assert some pointer is NULL

  @param pointer The pointer to check for NULL-ness

  @return An AssertionResult
*/
template <class T>
UnitTests::AssertionResult null(const T* value) throw () {

  UnitTests::AssertionResult cmp_result;
  if (value != 0){
    cmp_result.fail("Expected value to be NULL");
  }
  else {
    cmp_result.pass();
  }
  return cmp_result;
}

/**
  Assert some pointer is not NULL

  @param pointer The pointer to check for NULL-ness

  @return An AssertionResult
*/
template <class T>
UnitTests::AssertionResult not_null(const T* value) throw () {

  UnitTests::AssertionResult cmp_result;
  if (value == 0){
    cmp_result.fail("Expected value to be non-NULL");
  }
  else {
    cmp_result.pass();
  }
  return cmp_result;
}

/**
  Check that the result is greater than some expected value

  @param result The value which should be tested against the limit
  @param limit The number the result must be above

  @return An AssertionResult
*/
template <class T>
UnitTests::AssertionResult greater_than(const T& result, const T& limit) throw () {

  UnitTests::AssertionResult cmp_result;
  if (result <= limit){
    std::stringstream ss;
    ss << "'" << result << "' is not greater than '" << limit << "'";
    cmp_result.fail(ss.str().c_str());
  }
  else {
    cmp_result.pass();
  }
  return cmp_result;
}

/**
  Check that the result is greater than or equal to some expected value

  @param result The value which should be tested against the limit
  @param limit The number the result must be above or equal to

  @return An AssertionResult
*/
template <class T>
UnitTests::AssertionResult greater_than_or_equal(const T& result, const T& limit) throw () {

  UnitTests::AssertionResult cmp_result;
  if (result < limit){
    std::stringstream ss;
    ss << "'" << result << "' is not greater than or equal to '" << limit
      << "'";
    cmp_result.fail(ss.str().c_str());
  }
  else {
    cmp_result.pass();
  }
  return cmp_result;
}

/**
  Check that the result is less than some expected value

  @param result The value which should be tested against the limit
  @param limit The number the result must be below

  @return An AssertionResult
*/
template <class T>
UnitTests::AssertionResult less_than(const T& result, const T& limit) throw () {

  UnitTests::AssertionResult cmp_result;
  if (result >= limit){
    std::stringstream ss;
    ss << "'" << result << "' is not less than '" << limit << "'";
    cmp_result.fail(ss.str().c_str());
  }
  else {
    cmp_result.pass();
  }
  return cmp_result;
}

/**
  Check that the result is less than or equal to some expected value

  @param result The value which should be tested against the limit
  @param limit The number the result must be below or equal to

  @return An AssertionResult
*/
template <class T>
UnitTests::AssertionResult less_than_or_equal(const T& result, const T& limit) throw () {

  UnitTests::AssertionResult cmp_result;
  if (result > limit){
    std::stringstream ss;
    ss << "'" << result << "' is not less than or equal to '" << limit << "'";
    cmp_result.fail(ss.str().c_str());
  }
  else {
    cmp_result.pass();
  }
  return cmp_result;
}

#endif /* ASSERTIONS_H */
