#include "error_exception.h"

namespace UnitTests {

ErrorException::ErrorException(const std::string& _message) throw ():
  message(_message) {}

ErrorException::~ErrorException() throw () {}

} // namespace
