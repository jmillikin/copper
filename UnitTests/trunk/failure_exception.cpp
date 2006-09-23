#include "failure_exception.h"

namespace UnitTests {

FailureException::FailureException(
  const std::string& _assertion,
  const std::string& _message,
  const unsigned int _line) throw ():
  assertion(strdup(_assertion.c_str())),
  message(strdup(_message.c_str())),
  line(_line) {}

FailureException::~FailureException() throw () {
  free(const_cast<char*>(assertion));
  free(const_cast<char*>(message));
}

} // namespace
