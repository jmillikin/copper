/* test.cpp -- Runs a single unit test
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper/test.hpp>
#include <copper/suite.hpp>
#include "export.hpp"

namespace Copper {

EXPORT Test::Test(
  const String& _name,
  Suite* _suite,
  const String& _file_name) throw ():

  name(_name),
  suite(_suite),
  file_name(_file_name) {

  _suite->add_test(this);
}

EXPORT Test::~Test() {}

EXPORT List<Test> Test::all() {
  List<Test> all_tests;

  List<Suite> suites = Suite::all_suites();
  const ListNode<Suite>* suite = suites.root();

  while (suite) {
    List<Test> tests = suite->value->get_tests();
    const ListNode<Test>* test = tests.root();

    while (test) {
      all_tests.append(test->value);
      test = test->next;
    }

    suite = suite->next;
  }

  return all_tests;
}

Assertion* Test::run() {
  Assertion* bad_assertion = 0;
  set_up();
  _run(&bad_assertion);
  tear_down();
  return bad_assertion;
}

} // namespace
