/* exception_protector.cpp -- Guards against unexpected exceptions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <stdexcept>
#include <copper/protectors/exception_protector.hpp>
#include "../export.hpp"

namespace Copper {

EXPORT ExceptionProtector::ExceptionProtector() throw ():
  Protector() {}

EXPORT ExceptionProtector::~ExceptionProtector() throw () {}

void ExceptionProtector::_guard(Test* test, Assertion** failure,
  Error** error) {

#ifdef NO_EXCEPTIONS
  next_protector(test, failure, error);
#else
  try {
    next_protector(test, failure, error);
  }

  catch (const std::exception& e){
    String message = "Unhandled exception: ";
    *error = new Error(message + e.what());
  }

  catch (...){
    *error = new Error("Unhandled, unknown exception");
  }
#endif
}

} // namespace
