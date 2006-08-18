#ifndef ASSERTION_H
#define ASSERTION_H

// For formatting error strings
#include <sstream>

#include "failure_exception.h"

// Disable warnings about throw specifications in VS 2003
#pragma warning(disable: 4290)

/* Block any macro shenanigans from the standard library */
#ifdef assert
#undef assert
#endif

void assert(const std::string& assertion, const bool result,
  const unsigned int line) throw (UnitTests::FailureException);

void assert(const std::string& assertion, const std::string& result,
  const unsigned int line) throw (UnitTests::FailureException);

std::string failed(const std::string& assertion,
  const std::string& result) throw ();

std::string failed(const std::string& assertion, const bool result) throw ();

/**
  Assert two values are equal

  @param expected The expected value of this assertion
  @param result The value which should be tested against the expected value

  @returns An error string if the values are unequal, or "" if they are equal
*/
template <class T, class U>
std::string equal(const T& expected, const U& result) throw () {
  if (result != expected) {
    std::stringstream ss;
    ss << "Unequal values: expected '" << expected
      << "', got '" << result << "'";
    return ss.str();
  }
  return "";
}

/**
  An overloaded form of equal(), used for character strings. This transforms
  the char*s into std::strings

  @param expected The expected value of this assertion
  @param result The value which should be tested against the expected value

  @returns An error string if the values are unequal, or "" if they are equal
*/
template <>
inline std::string equal<const char*>(
  const char* const& expected,
  const char* const &result) throw () {

  return equal<std::string, std::string>(expected, result);
}

/**
  Check that the two values are nearly equal within a certain delta

  @param expected The expected value of this assertion
  @param result The value which should be tested against the expected value
  @param delta The allowable difference between the expected and actual
  values

  @returns An error string if the values are unequal, or "" if they are equal
  within the delta
*/
template <class T>
std::string equal_within(const T& expected, const T& result, const T& delta)
  throw () {

  if ((result < expected - delta) || (result > expected + delta)) {
    std::stringstream ss;
    ss << "Result '" << result << "' is not within '" << delta << "' of '"
        << expected << "'";
    return ss.str();
  }
  return "";
}

/**
  Assert two values are unequal

  @param bad Something that #actual should not be
  @param result The value which should be tested against the expected value

  @returns An error string if the values are equal, or "" if they are equal
*/
template <class T>
std::string unequal(const T& bad, const T& result) throw () {
  if (result == bad) {
    std::stringstream ss;
    ss << "'" << result << "' is equal to '" << bad << "'";
    return ss.str();
  }
  return "";
}

/**
  Assert some pointer is NULL

  @param pointer The pointer to check for NULL-ness

  @returns An error string if the pointer is not NULL, or "" if it is
*/
template <class T>
std::string null(const T* value) throw () {
  if (value != 0){
    return "Expected value to be NULL";
  }
  return "";
}

/**
  Assert some pointer is not NULL

  @param pointer The pointer to check for NULL-ness

  @returns An error string if the pointer is NULL, or "" if it isn't
*/
template <class T>
std::string not_null(const T* value) throw () {
  if (value == 0){
    return "Expected value to be non-NULL";
  }
  return "";
}

/**
  Check that the result is greater than some expected value

  @param result The value which should be tested against the limit
  @param limit The number the result must be above

  @returns An error string if result <= limit, or "" if not
*/
template <class T>
std::string greater_than(const T& result, const T& limit) throw () {
  if (result <= limit){
    std::stringstream ss;
    ss << "'" << result << "' is not greater than '" << limit << "'";
    return ss.str();
  }
  return "";
}

/**
  Check that the result is greater than or equal to some expected value

  @param result The value which should be tested against the limit
  @param limit The number the result must be above or equal to

  @returns An error string if result < limit, or "" if not
*/
template <class T>
std::string greater_than_or_equal(const T& result, const T& limit) throw () {
  if (result < limit){
    std::stringstream ss;
    ss << "'" << result << "' is not greater than or equal to '" << limit
      << "'";
    return ss.str();
  }
  return "";
}

/**
  Check that the result is less than some expected value

  @param result The value which should be tested against the limit
  @param limit The number the result must be below

  @returns An error string if result >= limit, or "" if not
*/
template <class T>
std::string less_than(const T& result, const T& limit) throw () {
  if (result >= limit){
    std::stringstream ss;
    ss << "'" << result << "' is not less than '" << limit << "'";
    return ss.str();
  }
  return "";
}

/**
  Check that the result is less than or equal to some expected value

  @param result The value which should be tested against the limit
  @param limit The number the result must be below or equal to

  @returns An error string if result > limit, or "" if not
*/
template <class T>
std::string less_than_or_equal(const T& result, const T& limit) throw () {
  if (result > limit){
    std::stringstream ss;
    ss << "'" << result << "' is not less than or equal to '" << limit << "'";
    return ss.str();
  }
  return "";
}

// Some macros for easier calling of assert() and failed()
#define assert(ASSERTION) assert(#ASSERTION, (ASSERTION), __LINE__)

#define failed(ASSERTION) failed(#ASSERTION, (ASSERTION))

#endif /* ASSERTION_H */
