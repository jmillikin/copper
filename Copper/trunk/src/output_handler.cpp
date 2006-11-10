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

EXPORT OutputHandler::OutputHandler(int&, char**&) {
  // For now, do nothing
}

EXPORT OutputHandler::~OutputHandler() {}

EXPORT void OutputHandler::run_test(Test* test) {
  begin(test);

  Assertion* failure = 0;
  Error* test_error = 0;

  Protector::guard(test, &failure, &test_error);

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

EXPORT void OutputHandler::run_tests(List<Test> tests) {
  const ListNode<Test>* node = tests.root();
  while (node) {
    run_test(node->value);
    node = node->next;
  }
}

} /* namespace */
