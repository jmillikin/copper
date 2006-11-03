/* assertion_result.cpp - The result of a single assertion
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <cstring>
#include <cstdlib>
#include <copper/assertion_result.hpp>
#include "export.hpp"

namespace Copper {

EXPORT AssertionResult::AssertionResult() throw ():
  m_finished(false), m_passed(false), m_failure_message(
    strdup("Unitialized AssertionResult")) {}

EXPORT AssertionResult::AssertionResult(bool result) throw ():
  m_finished(true), m_passed(result) {

  if (!passed()) {
    m_failure_message = strdup("Boolean assertion failed");
  }
  else {
    m_failure_message = strdup("No Error");
  }
}

AssertionResult::AssertionResult(const AssertionResult& other) throw () {
  m_finished = other.m_finished;
  m_passed = other.m_passed;
  m_failure_message = strdup(other.m_failure_message);
}

AssertionResult& AssertionResult::operator=(const AssertionResult& other)
  throw () {

  m_finished = other.m_finished;
  m_passed = other.m_passed;
  free(m_failure_message);
  m_failure_message = strdup(other.m_failure_message);

  return *this;
}

EXPORT AssertionResult::~AssertionResult() throw () {
  free(m_failure_message);
}

EXPORT const AssertionResult& AssertionResult::pass() throw () {
  if (!m_finished) {
    m_passed = true;
    m_finished = true;

    free(m_failure_message);
    m_failure_message = strdup("No Error");
  }
  return *this;
}

EXPORT const AssertionResult& AssertionResult::fail(
  const char* _failure_message) throw () {

  if (!m_finished) {
    m_passed = false;
    m_finished = true;

    free(m_failure_message);
    m_failure_message = strdup(_failure_message);
  }
  return *this;
}

EXPORT bool AssertionResult::passed() const throw () {
  return m_finished && m_passed;
}

EXPORT const char* AssertionResult::failure_message() const throw () {
  return m_failure_message;
}

} // namespace
