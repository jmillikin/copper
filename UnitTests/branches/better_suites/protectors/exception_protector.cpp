#include "exception_protector.h"

namespace UnitTests {

ExceptionProtector::ExceptionProtector() throw ():
  Protector() {}

ExceptionProtector::~ExceptionProtector() throw () {}

void ExceptionProtector::_guard(Test* test)
  throw (FailureException, ErrorException) {

  try {
    next_protector(test);
  }

  catch (const FailureException&){
    throw;
  }

  catch (const std::exception& e){
    throw ErrorException(std::string("Unhandled exception: ") + e.what());
  }

  catch (...){
    throw ErrorException("Unhandled, unknown exception");
  }
}

} // namespace
