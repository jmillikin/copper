/* self_tests.cpp - Various self-tests of the framework
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper.hpp>
#include <cstring>
#include <cstdlib>

// Undefine fail(), but it will be redefined later
#undef fail

#include <copper/output_handler.hpp>

// Various self-tests of the framework, to try and avoid bugs
TEST_SUITE(self_tests) {

FIXTURE(the_fixture) {
  int fixture_var = 0;
  bool set_up_finished = false;

  SET_UP {
    fixture_var = 1;
    set_up_finished = true;
  }
}

FIXTURE_TEST(fixture_test, the_fixture) {
  assert(equal(fixture_var, 1));
  assert(set_up_finished);
}

// Tests of implementation details

TEST(assertion_result_fresh) {
  Copper::AssertionResult ar;
  assert(!ar.passed());
  assert(equal("Unitialized AssertionResult", ar.failure_message()));
}

TEST(assertion_result_pass) {
  Copper::AssertionResult ar;
  ar.pass();

  assert(ar.passed());
  assert(equal("No Error", ar.failure_message()));

  ar.fail("Bad fail");
  assert(ar.passed());
  assert(equal("No Error", ar.failure_message()));
}

TEST(assertion_result_failure) {
  Copper::AssertionResult ar;
  ar.fail("Error goes here");

  assert(!ar.passed());
  assert(equal("Error goes here", ar.failure_message()));

  ar.pass();
  assert(!ar.passed());
  assert(equal("Error goes here", ar.failure_message()));
}

TEST(boolean_assertion_pass) {
  Copper::AssertionResult ar(true);

  assert(ar.passed());
}

TEST(boolean_assertion_failure) {
  Copper::AssertionResult ar(false);

  assert(!ar.passed());
  assert(equal("Boolean assertion failed", ar.failure_message()));
}

TEST(assertion_pass) {
  Copper::AssertionResult ar;
  ar.pass();
  Copper::Assertion a(ar, "Assertion text", 12345);

  assert(a.passed());
  assert(equal("Assertion text", a.text()));
  assert(equal(12345u, a.line()));
}

TEST(assertion_failure) {
  Copper::AssertionResult ar;
  ar.fail("Error goes here");
  Copper::Assertion a(ar, "Assertion text", 12345);

  assert(!a.passed());
  assert(equal("Assertion text", a.text()));
  assert(equal(12345u, a.line()));
  assert(equal("Error goes here", a.failure_message()));
}

TEST(assertion_failure_custom_message) {
  Copper::AssertionResult ar;
  ar.fail("Error goes here");
  Copper::Assertion a(ar, "Assertion text", "Custom error", 12345);

  assert(!a.passed());
  assert(equal("Assertion text", a.text()));
  assert(equal(12345u, a.line()));
  assert(equal("Custom error", a.failure_message()));
}

TEST(reverse_passed_assertion) {
  Copper::AssertionResult ar;
  ar.pass();
  Copper::AssertionResult reversed_ar = failed(ar);

  assert(!reversed_ar.passed());
  assert(equal("Unexpected success of assertion 'ar'",
    reversed_ar.failure_message()));
}

TEST(reverse_failed_assertion) {
  Copper::AssertionResult ar;
  ar.fail("");
  Copper::AssertionResult reversed_ar = failed(ar);

  assert(reversed_ar.passed());
}

}
