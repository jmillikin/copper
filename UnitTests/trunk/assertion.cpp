/* assertion.cpp - Asserts that certain statements are true
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "assertion.hpp"
#include "export.hpp"

namespace UnitTests {

EXPORT Assertion::Assertion(const AssertionResult& result, const char* _text,
  const unsigned int _line) throw ():

  m_result(result), m_text(strdup(_text)), m_line(_line) {}

EXPORT Assertion::Assertion(const Assertion& other) throw () {
  m_result = other.m_result;
  m_text = strdup(other.m_text);
  m_line = other.m_line;
}

Assertion& Assertion::operator=(const Assertion& other)
  throw () {

  m_result = other.m_result;
  m_text = strdup(other.m_text);
  m_line = other.m_line;
  return *this;
}

EXPORT Assertion::~Assertion() throw () {
  free(m_text);
}

EXPORT bool Assertion::passed() const throw () {
  return m_result.passed();
}

EXPORT const char* Assertion::text() const throw () {
  return m_text;
}

EXPORT unsigned int Assertion::line() const throw () {
  return m_line;
}

EXPORT const char* Assertion::failure_message() const throw () {
  return m_result.failure_message();
}

EXPORT UnitTests::AssertionResult failed_func(
  const UnitTests::Assertion& assertion) throw () {

  UnitTests::AssertionResult result;

  if (!assertion.passed()) {
    result.pass();
  }

  else {
    const char* text_str = assertion.text();
    const char* message_template = "Unexpected success of assertion '%s'";
    int message_size =
      // Size of the message template - 2 for the %s
      (strlen(message_template) - 2)
      + strlen(text_str) + 1; // size of the assertion text + 1 for NULL 
    char* message = static_cast<char*>(malloc(message_size));
    sprintf(message, message_template, text_str);
    result.fail(message);
    free(message);
  }

  return result;
}

} // namespace
