/* assertion.cpp - Asserts that certain statements are true
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/assertion.hpp>
#include "export.hpp"

namespace Copper {

EXPORT Assertion::Assertion(
  const AssertionResult& result,
  const String& text,
  const unsigned int line) throw ():

  m_result(result),
  m_text(text),
  m_line(line) {}

EXPORT Assertion::Assertion(
  const AssertionResult& result,
  const String& text,
  const String& message,
  const unsigned int line) throw ():

  m_result(result),
  m_text(text),
  m_message(message),
  m_line(line) {}

EXPORT Assertion::Assertion(bool, int) throw ():
  m_result (true),
  m_text (""),
  m_line (0) {}

EXPORT Assertion::Assertion(const Assertion& other) throw () {
  m_result = other.m_result;
  m_text = other.m_text;
  m_message = other.m_message;
  m_line = other.m_line;
}

const Assertion& Assertion::operator=(const Assertion& other)
  throw () {

  m_result = other.m_result;
  m_text = other.m_text;
  m_message = other.m_message;
  m_line = other.m_line;
  return *this;
}

EXPORT Assertion::~Assertion() throw () {}

EXPORT bool Assertion::passed() const throw () {
  return m_result.passed();
}

EXPORT const String& Assertion::text() const throw () {
  return m_text;
}

EXPORT unsigned int Assertion::line() const throw () {
  return m_line;
}

EXPORT const String& Assertion::failure_message() const throw () {
  if (m_message.size()) {
    return m_message;
  }

  else {
    return m_result.failure_message();
  }
}

EXPORT Copper::AssertionResult failed_func(
  const Copper::Assertion& assertion) throw () {

  Copper::AssertionResult result;

  if (!assertion.passed()) {
    result.pass();
  }

  else {
    String message =
      String("Unexpected success of assertion '") + assertion.text() + "'";
    result.fail(message);
  }

  return result;
}

} // namespace
