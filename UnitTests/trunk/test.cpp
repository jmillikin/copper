/* test.cpp -- Runs a single unit test
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "test.hpp"
#include "suite.hpp"

namespace UnitTests {

Test::Test(
  const char* _name,
  Suite* _suite,
  const char* _file_name) throw ():

  name(_name),
  suite(_suite),
  file_name(_file_name) {

  _suite->add_test(this);
}

Test::~Test() {}

void Test::run() {
  Assertion* bad_assertion = 0;
  set_up();
  _run(&bad_assertion);
  tear_down();
  if (bad_assertion) {
    FailureException exception = FailureException(
      bad_assertion->text(),
      bad_assertion->failure_message(),
      bad_assertion->line());
    delete bad_assertion;
    throw exception;
  }
}

} // namespace
