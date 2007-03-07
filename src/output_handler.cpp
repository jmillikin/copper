/* output_handler.cpp -- Base class for all output handlers
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <cstring>
#include <cstdlib>
#include <copper/output_handler.hpp>
#include <copper/protector.hpp>
#include <copper/assertion.hpp>
#include "export.hpp"

namespace Copper {

EXPORT OutputHandler::OutputHandler() {
  // For now, do nothing
}

EXPORT OutputHandler::~OutputHandler() {}

EXPORT void OutputHandler::run_test(Test* test, bool protect) {
  begin(test);

  Assertion* failure = 0;
  Error* test_error = 0;

  if (protect) {
    Protector::guard(test, &failure, &test_error);
  }
  
  else {
    test->run();
  }

  if (test_error) {
    error(test, test_error);
    delete test_error;
  }

  else if (failure) {
    fail(test, failure);
    delete failure;
  }

  else {
    pass(test);
  }
}

EXPORT void OutputHandler::run_tests(List<Test> tests, bool protect) {
  const ListNode<Test>* node = tests.root();
  while (node) {
    run_test(node->value, protect);
    node = node->next;
  }
}

EXPORT List<Test> OutputHandler::parse_test_args(int argc, char** argv) {
  List<Test> all_tests = Test::all();
  return all_tests;
}

} /* namespace */
