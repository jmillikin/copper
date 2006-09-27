/* assertion_result.cpp - The result of a single assertion
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <cstring>
#include <cstdlib>
#include "assertion_result.hpp"

namespace UnitTests {

AssertionResult::AssertionResult() throw ():
  m_finished(false) {}

AssertionResult::AssertionResult(bool result) throw ():
  m_finished(true), m_passed(result) {

  if (!passed()) {
    m_failure_message = strdup("Boolean assertion failed");
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

} // namespace
