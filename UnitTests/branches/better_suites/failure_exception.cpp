#include "failure_exception.h"

namespace UnitTests {

FailureException::FailureException(
  const std::string& _assertion,
  const std::string& _error,
  const unsigned int _line) throw ():
  assertion(_assertion), error(_error), line(_line) {}

FailureException::~FailureException() throw () {}

} // namespace
