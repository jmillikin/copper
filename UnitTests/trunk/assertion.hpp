/* assertion.hpp - Asserts that certain statements are true
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "failure_exception.hpp"
#include "assertions.hpp"

#ifndef ASSERTION_HPP
#define ASSERTION_HPP

namespace UnitTests {

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

  /** Copy constructor */
  Assertion(const Assertion& other) throw ();

  /** Assignment operator */
  Assertion& operator=(const Assertion& other) throw ();

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

  /** TEMPORARY */
  void check() const throw (FailureException);

protected:
  /** The result of running this assertion */
  AssertionResult m_result;

  /** The code that this Assertion tests */
  char* m_text;

  /** The line this Assertion is located on */
  unsigned int m_line;
};

UnitTests::AssertionResult failed_func(const UnitTests::Assertion& assertion) throw ();

} // namespace

// Some macros for easier calling of assert() and failed()
#define assert(ASSERTION) UnitTests::Assertion(ASSERTION, #ASSERTION, __LINE__).check()

#define failed(ASSERTION) UnitTests::failed_func(UnitTests::Assertion(ASSERTION, #ASSERTION, __LINE__))

// Macro for checking if an exception was thrown
/*
#define assert_throws(CODE, EXCEPTION_TYPE) \
  try {\
    CODE;\
    assert_func("assert_throws("#CODE", "#EXCEPTION_TYPE")",\
      std::string(#CODE" threw no exceptions"), __LINE__);\
  }\
  catch (const EXCEPTION_TYPE&) {}
*/
#define assert_throws(CODE, EXCEPTION_TYPE) \
  UnitTests::Assertion(false, "assert_throws unimplemented", __LINE__).check()

#endif /* ASSERTION_HPP */
