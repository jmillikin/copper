/* test.cpp -- Runs a single unit test
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "test.h"
#include "suite.h"

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

Assertion* Test::run() {
  Assertion* result = 0;
  set_up();
  _run(&result);
  tear_down();
  return result;
}

} // namespace
