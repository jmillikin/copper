/* output_handler.cpp -- Base class for all output handlers
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <algorithm>
#include "output_handler.hpp"
#include "protector.hpp"
#include "protectors/exception_protector.hpp"
#include "assertion.hpp"

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

std::string OutputHandler::pretty_name(std::string name) throw () {
  // Search for an upper-case letter, to ensure this won't make two upper-case
  // letters in a row
  std::string::size_type upper_index = name.find_first_of(
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

  // Search for the first lower-case letter
  std::string::size_type lower_index = name.find_first_of(
    "abcdefghijklmnopqrstuvwxyz", 0, upper_index);

  if (lower_index != std::string::npos && lower_index < upper_index) {
    name[lower_index] -= 32;
  }

  // Convert underscores to spaces
  std::replace(name.begin(), name.end(), '_', ' ');

  return name;
}

void OutputHandler::run_test(Test* test) {
  try {
    begin(test);
    Assertion* failed = Protector::guard(test);
    if (failed) {
      fail(test, failed);
      delete failed;
    }
    else {
      pass(test);
    }
  }

  catch (const ErrorException& e) {
    error(test, e); 
  }
}

} /* namespace */
