/* assertion.cpp - Asserts that certain statements are true
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "assertion.h"

namespace UnitTests {

AssertionResult::AssertionResult() throw ():
  m_finished(false) {}

AssertionResult::AssertionResult(bool result) throw ():
  m_finished(true), m_passed(result) {

  if (!passed()) {
    m_failure_message = strdup("Boolean asssertion failed");
  }
}

AssertionResult::AssertionResult(const AssertionResult& other) throw () {
  m_finished = other.m_finished;
  m_passed = other.m_passed;
  if (m_finished && !m_passed) {
    m_failure_message = strdup(other.m_failure_message);
  }
}

AssertionResult& AssertionResult::operator=(const AssertionResult& other)
  throw () {

  m_finished = other.m_finished;
  m_passed = other.m_passed;
  if (m_finished && !m_passed) {
    m_failure_message = strdup(other.m_failure_message);
  }

  return *this;
}

AssertionResult::~AssertionResult() throw () {
  if (failure_message()) {
    free(m_failure_message);
  }
}

void AssertionResult::pass() throw () {
  if (!m_finished) {
    m_passed = true;
    m_finished = true;
  }
}

void AssertionResult::fail(const char* _failure_message) throw () {
  if (!m_finished) {
    m_passed = false;
    m_failure_message = strdup(_failure_message);
    m_finished = true;
  }
}

bool AssertionResult::passed() const throw () {
  return m_finished && m_passed;
}

const char* AssertionResult::failure_message() const throw () {
  if (m_finished && !m_passed) {
    return m_failure_message;
  }
  else {
    return 0;
  }
}

Assertion::Assertion(const AssertionResult& result, const char* _text,
  const unsigned int line) throw ():

  m_result(result), m_text(strdup(_text)), m_line(line) {}

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

}

UnitTests::AssertionResult failed(const UnitTests::AssertionResult& result)
  throw () {

  UnitTests::AssertionResult new_result;
  if (result.passed()) {
    new_result.fail("Unexpected sucess of assertion");
  }
  else {
    new_result.pass();
  }
  return new_result;
}

UnitTests::AssertionResult equal(char const* result, char const* expected)
  throw () {

  std::string s_result = result, s_expected = expected;
  return equal(s_result, s_expected);
}

UnitTests::AssertionResult unequal(char const* bad, char const* result)
  throw () {

  std::string s_result = result, s_bad = bad;
  return unequal(s_bad, s_result);
}
