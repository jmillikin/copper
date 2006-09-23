#include "error_exception.h"

namespace UnitTests {

ErrorException::ErrorException(const std::string& _message) throw ():
  message(strdup(_message.c_str())) {}

ErrorException::~ErrorException() throw () {
  free(const_cast<char*>(message));
}

} // namespace
