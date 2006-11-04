/* assertion_result.hpp - The result of a single assertion
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef COPPER_ASSERTION_RESULT_HPP
#define COPPER_ASSERTION_RESULT_HPP

// Disable warnings about throw specifications in VS 2003
#ifdef _MSC_VER
#pragma warning(disable: 4290)
#endif

namespace Copper {

class AssertionResult {
public:
  /** Default constructor */
  AssertionResult() throw ();

  /** Construct from a boolean value */
  AssertionResult(bool result) throw ();

  /** Copy constructor */
  AssertionResult(const AssertionResult& other) throw ();

  /** Assignment operator */
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

} // namespace

#endif /* COPPER_ASSERTION_RESULT_HPP */
