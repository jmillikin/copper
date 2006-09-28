/* failure_exception.cpp -- Thrown when an assertion fails
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "failure_exception.hpp"

namespace UnitTests {

FailureException::FailureException(
  const std::string& _assertion,
  const std::string& _message,
  const unsigned int _line) throw ():
  assertion(strdup(_assertion.c_str())),
  message(strdup(_message.c_str())),
  line(_line) {}


FailureException::FailureException(const FailureException& other) throw ():
  assertion(strdup(other.assertion)),
  message(strdup(other.message)),
  line(other.line) {}

FailureException::~FailureException() throw () {
  free(const_cast<char*>(assertion));
  free(const_cast<char*>(message));
}

} // namespace
