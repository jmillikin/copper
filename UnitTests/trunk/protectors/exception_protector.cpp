/* exception_protector.cpp -- Guards against unexpected exceptions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "exception_protector.hpp"

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
    throw ErrorException(std::string("Unhandled exception: ") + e.what());
  }

  catch (...){
    throw ErrorException("Unhandled, unknown exception");
  }
}

} // namespace
