#include "output_handler.h"
#include "protector.h"

namespace UnitTests {

OutputHandler::OutputHandler() {}

OutputHandler::~OutputHandler() {}

void OutputHandler::run_test(Test* test) {
  try {
    begin(test);
    Protector::guard(test);
    pass(test);
  }

  catch (const FailureException& e) {
    fail(test, e); 
  }

  catch (const ErrorException& e) {
    error(test, e); 
  }
}

} /* namespace */
