/* output_handler.cpp -- Base class for all output handlers
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <algorithm>
#include <copper/output_handler.hpp>
#include <copper/protector.hpp>
#include <copper/assertion.hpp>
#include "export.hpp"

namespace Copper {

OutputHandler::OutputHandler(int&, char**&) {
  // For now, do nothing
}

OutputHandler::~OutputHandler() {}

EXPORT std::string OutputHandler::pretty_name(std::string name) throw () {
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
  begin(test);

  Assertion* failure = 0;
  Error* test_error = 0;

  Protector::guard(test, &failure, &test_error);

  if (failure) {
    fail(test, failure);
    delete failure;
  }

  if (test_error) {
    error(test, test_error);
    delete test_error;
  }

  pass(test);
}

} /* namespace */
