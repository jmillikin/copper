/* exception_protector.cpp -- Guards against unexpected exceptions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "exception_protector.hpp"
#include <cstdio>
#include <stdexcept>

namespace UnitTests {

ExceptionProtector::ExceptionProtector() throw ():
  Protector() {}

ExceptionProtector::~ExceptionProtector() throw () {}

void ExceptionProtector::_guard(Test* test, Assertion** failure,
  Error** error) {

#ifdef NO_EXCEPTIONS
  next_protector(test, failure, error);
#else
  try {
    next_protector(test, failure, error);
  }

  catch (const std::exception& e){
    const char* message_template = "Unhandled exception: %s";
    const char* exception_message = e.what();
    char* message = static_cast<char*>(malloc(
      strlen(message_template) - 2
      + strlen(exception_message)
      + 1));
    sprintf(message, message_template, exception_message);
    *error = new Error(message);
    free(message);
  }

  catch (...){
    *error = new Error("Unhandled, unknown exception");
  }
#endif
}

} // namespace
