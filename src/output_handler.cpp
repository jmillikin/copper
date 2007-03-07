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

Suite* find_suite(const char* name) {
  // Find all suites
  List<Suite> all = Suite::all_suites();

  const ListNode<Suite>* node = all.root();
  while (node) {
    Suite* suite = node->value;
    if (suite->name == name) {
      return suite;
    }
    node = node->next;
  }

  return NULL;
}

Test* find_test(const char* full_name) {
  // Separate the full name into suite name and test name
  int len = strlen(full_name);
  char* suite_name = new char[len+1];
  strcpy(suite_name, full_name);
  char* midpoint = strchr(suite_name, '.');
  char* test_name = midpoint + 1;
  *midpoint = 0;

  // Find the suite
  Suite* suite = find_suite(suite_name);

  if (!suite) {
    delete[] suite_name;
    return NULL;
  }

  // Find the test
  List<Test> suite_tests = suite->get_tests();
  const ListNode<Test>* node = suite_tests.root();
  while (node) {
    Test* test = node->value;
    if (test->name == test_name) {
      delete[] suite_name;
      return test;
    }
    node = node->next;
  }

  delete[] suite_name;
  return NULL;
}

EXPORT List<Test> OutputHandler::parse_test_args(int argc, char** argv) {
  List<Test> tests;

  for (int ii = 0; ii < argc; ii++) {
    const char* name = argv[ii];
    const char* midpoint = strchr(name, '.');

    if (midpoint) {
      // This name includes a test name
      Test* test = find_test(name);
      if (test) {
        tests.append(test);
      }
    }

    else {
      // No test name, append everything in the suite
      Suite* suite = find_suite(name);

      if (suite) {
        List<Test> suite_tests = suite->get_tests();
        const ListNode<Test>* node = suite_tests.root();
        while (node) {
          tests.append(node->value);
          node = node->next;
        }
      }
    }
  }

  if (tests.size()) {
    return tests;
  }

  else {
    return Test::all();
  }
}

} /* namespace */
