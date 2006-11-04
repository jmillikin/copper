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

EXPORT OutputHandler::OutputHandler(int&, char**&) {
  // For now, do nothing
}

EXPORT OutputHandler::~OutputHandler() {}

EXPORT char* OutputHandler::pretty_name(const char* old_name) throw () {
  char* name = strdup(old_name);

  // Search for an upper-case letter, to ensure this won't make two upper-case
  // letters in a row
  size_t upper_index = strcspn(name, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  size_t lower_index = strcspn(name, "abcdefghijklmnopqrstuvwxyz");

  // If a lower case letter appears before an upper-case letter, make it
  // uppercase also
  if (lower_index < upper_index) {
    name[lower_index] -= 32;
  }

  size_t len = strlen(name);
  // Convert underscores to spaces
  for (size_t ii = 0; ii < len; ii++) {
    if (name[ii] == '_') {
      name[ii] = ' ';
    }
  }

  return name;
}

EXPORT void OutputHandler::run_test(Test* test) {
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

EXPORT void OutputHandler::run_tests(List<Test> tests) {
  const ListNode<Test>* node = tests.root();
  while (node) {
    run_test(node->value);
    node = node->next;
  }
}

} /* namespace */
