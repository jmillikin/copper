#include "failure_exception.h"

namespace UnitTests {

FailureException::FailureException(const std::string& _message) throw ():
  message(_message){}

FailureException::~FailureException() throw () {}

const std::string& FailureException::get_message() const throw (){
  return message;
}

} // namespace
