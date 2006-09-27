/* output_handler.cpp -- Base class for all output handlers
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "output_handler.hpp"
#include "protector.hpp"
#include "protectors/exception_protector.hpp"

namespace UnitTests {

OutputHandler::OutputHandler(int& argc, char**& argv) {
  // Allow exception catching to be toggled on or off at runtime
  bool catch_exceptions = true;
  for (int ii = 1; ii < argc; ii++) {
    if (strcmp(argv[ii], "--no-exceptions") == 0) {
      catch_exceptions = false;
    }   
  }

  if (catch_exceptions) {
    static ExceptionProtector exception_protector;
    Protector::add(&exception_protector);
  }
}

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
