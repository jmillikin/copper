#include "failure_exception.h"

namespace UnitTests {

FailureException::FailureException(
  const std::string& _assertion,
  const std::string& _message,
  const unsigned int _line) throw ():
  assertion(_assertion), message(_message), line(_line) {}

FailureException::~FailureException() throw () {}

} // namespace
