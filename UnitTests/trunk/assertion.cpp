/* assertion.cpp - Asserts that certain statements are true
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "assertion.hpp"

namespace UnitTests {

Assertion::Assertion(const AssertionResult& result, const char* _text,
  const unsigned int _line) throw ():

  m_result(result), m_text(strdup(_text)), m_line(_line) {}

Assertion::Assertion(const Assertion& other) throw () {
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

Assertion::~Assertion() throw () {
  free(m_text);
}

bool Assertion::passed() const throw () {
  return m_result.passed();
}

const char* Assertion::text() const throw () {
  return m_text;
}

unsigned int Assertion::line() const throw () {
  return m_line;
}

const char* Assertion::failure_message() const throw () {
  return m_result.failure_message();
}

void Assertion::check() const throw (FailureException) {
  if (!passed()) {
    throw FailureException(text(), failure_message(), line());
  }
}

UnitTests::AssertionResult failed_func(const UnitTests::Assertion& assertion) throw () {
  UnitTests::AssertionResult result;

  if (!assertion.passed()) {
    result.pass();
  }

  else {
    std::string message = "Unexpected sucess of assertion '";
    message = message + assertion.text() + "'";
    result.fail(message.c_str());
  }

  return result;
}

} // namespace
