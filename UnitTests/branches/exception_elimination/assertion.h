/* assertion.h - Asserts that certain statements are true
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef ASSERTION_H
#define ASSERTION_H

// For formatting failure strings
#include <sstream>

// Disable warnings about throw specifications in VS 2003
#ifdef _MSC_VER
#pragma warning(disable: 4290)
#endif

/* Block any macro shenanigans from the standard library */
#ifdef assert
#undef assert
#endif

namespace UnitTests {

class AssertionResult {
public:
  /** Default constructor */
  AssertionResult() throw ();

  /** Construct from a boolean value */
  AssertionResult(bool result) throw ();

  /** Copy constructor */
  AssertionResult(const AssertionResult& other) throw ();

  AssertionResult& operator=(const AssertionResult& other) throw ();

  /** Default destructor */
  ~AssertionResult() throw ();

  /** Mark that the Assertion has passed */
  void pass() throw ();

  /**
    Mark that the Assertion has failed

    @param message The failure message
  */
  void fail(const char* failure_message) throw ();

  /** Get whether the Assertion has passed or failed */
  bool passed() const throw ();

  /** If the Assertion failed, get the failure message */
  const char* failure_message() const throw ();

protected:
  /** True if pass() or fail() has been called */
  bool m_finished;

  /** Whether the Assertion has passed or failed */
  bool m_passed;

  /** If the Assertion failed, this will contain the failure message */
  char* m_failure_message;
};

class Assertion {
public:
  /**
    Create a new assertion with the result of an assertion function

    @param result The result of running this Assertion
    @param text The code that this Assertion tests
    @param line The line this Assertion is located on
  */
  Assertion(const AssertionResult& result, const char* text,
    const unsigned int line) throw ();

  /** Default destructor */
  ~Assertion() throw ();

  /** Whether this Assertion has pased or failed */
  bool passed() const throw ();

  /** Get the code that this Assertion tests */
  const char* text() const throw ();

  /** Get the line this Assertion is located on */
  unsigned int line() const throw ();

  /** If this Assertion failed, get the failure message */
  const char* failure_message() const throw ();

protected:
  /** The result of running this assertion */
  const AssertionResult m_result;

  /** The code that this Assertion tests */
  char* m_text;

  /** The line this Assertion is located on */
  unsigned int m_line;
};

} // namespace

/**
  Assert another assertion failed

  @param result An AssertionResult from a previous assertion
  @return The reverse of result
*/
UnitTests::AssertionResult failed(const UnitTests::AssertionResult& result)
  throw ();

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
    return "Expected value to be NULL";
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
    return "Expected value to be non-NULL";
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

// Some macros for easier calling of assert() and failed()
#define assert(ASSERTION) UnitTests::Assertion(\
  (ASSERTION), #ASSERTION, __LINE__)

// Macro for checking if an exception was thrown
#define assert_throws(CODE, EXCEPTION_TYPE) \
  try {\
    UnitTests::AssertionResult test_ar;\
    CODE;\
    test_ar.fail(#CODE" threw no exceptions");\
    assert(test_ar);\
  }\
  catch (const EXCEPTION_TYPE&) {}

#endif /* ASSERTION_H */
