/* exception_protector.cpp -- Guards against unexpected exceptions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "exception_protector.hpp"
#include <stdexcept>

namespace UnitTests {

ExceptionProtector::ExceptionProtector() throw ():
  Protector() {}

ExceptionProtector::~ExceptionProtector() throw () {}

Assertion* ExceptionProtector::_guard(Test* test)
  throw (ErrorException) {

  try {
    return next_protector(test);
  }

  catch (const std::exception& e){
    const char* message_template = "Unhandled exception: %s";
    const char* exception_message = e.what();
    char* message = static_cast<char*>(malloc(
      strlen(message_template) - 2
      + strlen(exception_message)
      + 1));
    sprintf(message, message_template, exception_message);
    ErrorException exception(message);
    free(message);
    throw exception;
  }

  catch (...){
    throw ErrorException("Unhandled, unknown exception");
  }
}

} // namespace
