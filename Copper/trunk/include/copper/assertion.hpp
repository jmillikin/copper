/* assertion.hpp - Asserts that certain statements are true
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper/util/string.hpp>
#include <copper/assertion_result.hpp>

#ifndef COPPER_ASSERTION_HPP
#define COPPER_ASSERTION_HPP

namespace Copper {

class Assertion {
public:
  /**
    Create a new assertion with the result of an assertion function

    @param result The result of running this Assertion
    @param text The code that this Assertion tests
    @param line The line this Assertion is located on
  */
  Assertion(const AssertionResult& result, const String& text,
    const unsigned int line) throw ();

  /**
    Create a new assertion with the result of an assertion function

    @param result The result of running this Assertion
    @param text The code that this Assertion tests
    @param message If the assertion failed, this message will be used
      instead of the error message from the check
    @param line The line this Assertion is located on
  */
  Assertion(const AssertionResult& result, const String& text,
    const String& message, const unsigned int line) throw ();

  /** Copy constructor */
  Assertion(const Assertion& other) throw ();

  /** Assignment operator */
  const Assertion& operator=(const Assertion& other) throw ();

  /** Default destructor */
  ~Assertion() throw ();

  /** Whether this Assertion has pased or failed */
  bool passed() const throw ();

  /** Get the code that this Assertion tests */
  const String& text() const throw ();

  /** Get the line this Assertion is located on */
  unsigned int line() const throw ();

  /** If this Assertion failed, get the failure message */
  const String& failure_message() const throw ();

protected:
  /** The result of running this assertion */
  AssertionResult m_result;

  /** The code that this Assertion tests */
  String m_text;

  /** The custom message passed to assert, if available */
  String m_message;

  /** The line this Assertion is located on */
  unsigned int m_line;
};

Copper::AssertionResult failed_func(const Copper::Assertion& assertion) throw ();

} // namespace

#endif /* COPPER_ASSERTION_HPP */
