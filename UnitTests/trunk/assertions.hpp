/* assertions.hpp - Available assertions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef ASSERTIONS_HPP
#define ASSERTIONS_HPP

// For formatting error strings
#include <sstream>

#include "assertion_result.hpp"
#include "assertion.hpp"

// Disable warnings about throw specifications in VS 2003
#ifdef _MSC_VER
#pragma warning(disable: 4290)
#endif

/**
  Assert two values are equal

  @param expected The expected value of this assertion
  @param actual The value which should be tested against the expected value

  @return An AssertionResult
*/
template <class Expected, class Actual>
UnitTests::AssertionResult equal(
  const Expected& expected,
  const Actual& actual) throw () {

  UnitTests::AssertionResult result;
  if (expected != actual) {
    std::stringstream ss;
    ss << "Unequal values: expected '" << expected
      << "', got '" << actual << "'";
    result.fail(ss.str().c_str());
  }
  else {
    result.pass();
  }
  return result;
}

/**
  An overloaded form of equal(), used for character strings. This transforms
  the char*s into std::strings

  @param expected The expected value of this assertion
  @param actual The value which should be tested against the expected value

  @return An AssertionResult
*/
UnitTests::AssertionResult equal(char const* expected, char const* actual)
  throw ();

/**
  Check that the two values are nearly equal within a certain delta

  @param result The value which should be tested against the expected value
  @param expected The expected value of this assertion
  @param delta The allowable difference between the expected and actual
  values

  @return An AssertionResult
*/
template <class Value>
UnitTests::AssertionResult equal_within(
  const Value& expected,
  const Value& actual,
  const Value& delta) throw () {

  UnitTests::AssertionResult result;
  if ((actual < expected - delta) || (actual > expected + delta)) {
    std::stringstream ss;
    ss << "'" << actual << "' is not within '" << delta << "' of '"
        << expected << "'";
    result.fail(ss.str().c_str());
  }
  else {
    result.pass();
  }
  return result;
}

/**
  Assert two values are unequal

  @param bad Something that #actual should not be
  @param actual The value which should be tested against the expected value

  @return An AssertionResult
*/
template <class Bad, class Actual>
UnitTests::AssertionResult unequal(
  const Bad& bad,
  const Actual& actual) throw () {

  UnitTests::AssertionResult result;
  if (actual == bad) {
    std::stringstream ss;
    ss << "'" << actual << "' is equal to '" << bad << "'";
    result.fail(ss.str().c_str());
  }
  else {
    result.pass();
  }
  return result;
}

/**
  An overloaded form of unequal(), used for character strings. This transforms
  the char*s into std::strings

  @param bad Something that #actual should not be
  @param actual The value which should be tested against the expected value

  @return An AssertionResult
*/
UnitTests::AssertionResult unequal(char const* bad, char const* actual)
  throw ();

/**
  Assert some pointer is NULL

  @param pointer The pointer to check for NULL-ness

  @return An AssertionResult
*/
template <class Value>
UnitTests::AssertionResult null(const Value* value) throw () {

  UnitTests::AssertionResult result;
  if (value != 0){
    result.fail("Expected value to be NULL");
  }
  else {
    result.pass();
  }
  return result;
}

/**
  Assert some pointer is not NULL

  @param pointer The pointer to check for NULL-ness

  @return An AssertionResult
*/
template <class Value>
UnitTests::AssertionResult not_null(const Value* value) throw () {

  UnitTests::AssertionResult result;
  if (value == 0){
    result.fail("Expected value to be non-NULL");
  }
  else {
    result.pass();
  }
  return result;
}

/**
  Check that the result is greater than some expected value

  @param actual The value which should be tested against the limit
  @param limit The value the result must be above

  @return An AssertionResult
*/
template <class Value>
UnitTests::AssertionResult greater_than(
  const Value& actual,
  const Value& limit) throw () {

  UnitTests::AssertionResult result;
  if (actual <= limit){
    std::stringstream ss;
    ss << "'" << actual << "' is not greater than '" << limit << "'";
    result.fail(ss.str().c_str());
  }
  else {
    result.pass();
  }
  return result;
}

/**
  Check that the result is greater than or equal to some expected value

  @param actual The value which should be tested against the limit
  @param limit The number the result must be above or equal to

  @return An AssertionResult
*/
template <class Value>
UnitTests::AssertionResult greater_than_or_equal(
  const Value& actual,
  const Value& limit) throw () {

  UnitTests::AssertionResult result;
  if (actual < limit){
    std::stringstream ss;
    ss << "'" << actual << "' is less than '" << limit << "'";
    result.fail(ss.str().c_str());
  }
  else {
    result.pass();
  }
  return result;
}

/**
  Check that the result is less than some expected value

  @param actual The value which should be tested against the limit
  @param limit The number the result must be below

  @return An AssertionResult
*/
template <class Value>
UnitTests::AssertionResult less_than(
  const Value& actual,
  const Value& limit) throw () {

  UnitTests::AssertionResult result;
  if (actual >= limit){
    std::stringstream ss;
    ss << "'" << actual << "' is not less than '" << limit << "'";
    result.fail(ss.str().c_str());
  }
  else {
    result.pass();
  }
  return result;
}

/**
  Check that the result is less than or equal to some expected value

  @param result The value which should be tested against the limit
  @param limit The number the result must be below or equal to

  @return An AssertionResult
*/
template <class Value>
UnitTests::AssertionResult less_than_or_equal(
  const Value& actual,
  const Value& limit) throw () {

  UnitTests::AssertionResult result;
  if (actual > limit){
    std::stringstream ss;
    ss << "'" << actual << "' is not less than or equal to '" << limit << "'";
    result.fail(ss.str().c_str());
  }
  else {
    result.pass();
  }
  return result;
}

#endif /* ASSERTIONS_HPP */
