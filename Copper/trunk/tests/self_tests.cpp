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
TEST_SUITE("Self tests") {

TEST("boolean true") {
  assert(true);
}

TEST("assert failed") {
  // Check that a failed test will result in a pass
  assert(failed(false));
}

TEST("assert failed fail") {
  // Check that a passing test will result in a fail
  assert(failed(failed(true)));
}

TEST("integer equals") {
  assert(equal(2, 2));
}

TEST("integer equals fail") {
  assert(failed(equal(1, 2)));
}

FIXTURE(str_fixture) {
  const Copper::String
    var1 = "test",
    var2 = "test",
    var3 = "other",
    var4 = "other";
  char* cvar1, *cvar2, *cvar3, *cvar4;

  SET_UP {
    cvar1 = Copper::strdup(var1.c_str());
    cvar2 = Copper::strdup(var2.c_str());
    cvar3 = Copper::strdup(var3.c_str());
    cvar4 = Copper::strdup(var4.c_str());
  }

  TEAR_DOWN {
    std::free(cvar1);
    std::free(cvar2);
    std::free(cvar3);
    std::free(cvar4);
  }
}

FIXTURE_TEST("Copper::String equal", str_fixture) {
  assert(equal(var1, var2));
}

FIXTURE_TEST("Copper::String equal fail", str_fixture) {
  assert(failed(equal(var1, var3)));
}

FIXTURE_TEST("char* equal", str_fixture) {
  // Confirm that the addresses are not being compared
  assert(cvar1 != cvar2);

  assert(equal("test", "test"));
  assert(equal(cvar1, "test"));
  assert(equal(cvar1, cvar2));
}

FIXTURE_TEST("char* equal fail", str_fixture) {
  assert(failed(equal(cvar1, cvar3)));
}

FIXTURE_TEST("mixed string equality", str_fixture) {
  assert(equal(var1, cvar1));
  assert(equal(var2, cvar1));
}

FIXTURE_TEST("mixed string equality fail", str_fixture) {
  assert(failed(equal(var1, cvar3)));
}

FIXTURE_TEST("Copper::String unequal", str_fixture) {
  assert(unequal(var1, var3));
}

FIXTURE_TEST("Copper::String unequal fail", str_fixture) {
  assert(failed(unequal(var3, var4)));
}

FIXTURE_TEST("char* unequal", str_fixture) {
  assert(unequal("test", "other"));
  assert(unequal(cvar1, "other"));
  assert(unequal(cvar1, cvar3));
}

FIXTURE_TEST("char* unequal fail", str_fixture) {
  assert(failed(unequal(cvar3, cvar4)));
}

FIXTURE_TEST("mixed string inequality", str_fixture) {
  assert(unequal(var1, cvar3));
}

FIXTURE_TEST("mixed string inequality fail", str_fixture) {
  assert(failed(unequal(var1, cvar2)));
}

TEST("equal within") {
  assert(equal_within(2.0, 2.0001, 0.001));
}

TEST("equal within fail") {
  assert(failed(equal_within(2.0, 2.01, 0.001)));
}

TEST("unequal") {
  assert(unequal(1, 2));
}

TEST("unequal fail") {
  assert(failed(unequal(2, 2)));
}

TEST("is null") {
  int* var = 0;
  assert(null(var));
}

TEST("is null fail") {
  int var;
  assert(failed(null(&var)));
}

TEST("not null") {
  int var;
  assert(not_null(&var));
}

TEST("not null fail") {
  int* var = 0;
  assert(failed(not_null(var)));
}

TEST("greater than") {
  assert(greater_than(2, 1));
}

TEST("greater than fail") {
  assert(failed(greater_than(2, 2)));
  assert(failed(greater_than(2, 3)));
}

TEST("greater than or equal") {
  assert(greater_than_or_equal(2, 2));
  assert(greater_than_or_equal(2, 1));
}

TEST("greater than or equal fail") {
  assert(failed(greater_than_or_equal(1, 2)));
}

TEST("less than") {
  assert(less_than(1, 2));
}

TEST("less than fail") {
  assert(failed(less_than(2, 2)));
  assert(failed(less_than(2, 1)));
}

TEST("less than or equal") {
  assert(less_than_or_equal(1, 2));
  assert(less_than_or_equal(2, 2));
}

TEST("less than or equal fail") {
  assert(failed(less_than_or_equal(2, 1)));
}

FIXTURE(the_fixture) {
  int fixture_var = 0;
  bool set_up_finished = false;

  SET_UP {
    fixture_var = 1;
    set_up_finished = true;
  }
}

FIXTURE_TEST("fixture test", the_fixture) {
  assert(equal(fixture_var, 1));
  assert(set_up_finished);
}

// Tests of implementation details

TEST("assertion result fresh") {
  Copper::AssertionResult ar;
  assert(!ar.passed());
  assert(equal("Unitialized AssertionResult", ar.failure_message()));
}

TEST("assertion result pass") {
  Copper::AssertionResult ar;
  ar.pass();

  assert(ar.passed());
  assert(equal("No Error", ar.failure_message()));

  ar.fail("Bad fail");
  assert(ar.passed());
  assert(equal("No Error", ar.failure_message()));
}

TEST("assertion result failure") {
  Copper::AssertionResult ar;
  ar.fail("Error goes here");

  assert(!ar.passed());
  assert(equal("Error goes here", ar.failure_message()));

  ar.pass();
  assert(!ar.passed());
  assert(equal("Error goes here", ar.failure_message()));
}

TEST("boolean assertion pass") {
  Copper::AssertionResult ar(true);

  assert(ar.passed());
}

TEST("boolean assertion failure") {
  Copper::AssertionResult ar(false);

  assert(!ar.passed());
  assert(equal("Boolean assertion failed", ar.failure_message()));
}

TEST("assertion pass") {
  Copper::AssertionResult ar;
  ar.pass();
  Copper::Assertion a(ar, "Assertion text", 12345);

  assert(a.passed());
  assert(equal("Assertion text", a.text()));
  assert(equal(12345u, a.line()));
}

TEST("assertion failure") {
  Copper::AssertionResult ar;
  ar.fail("Error goes here");
  Copper::Assertion a(ar, "Assertion text", 12345);

  assert(!a.passed());
  assert(equal("Assertion text", a.text()));
  assert(equal(12345u, a.line()));
  assert(equal("Error goes here", a.failure_message()));
}

TEST("assertion failure custom message") {
  Copper::AssertionResult ar;
  ar.fail("Error goes here");
  Copper::Assertion a(ar, "Assertion text", "Custom error", 12345);

  assert(!a.passed());
  assert(equal("Assertion text", a.text()));
  assert(equal(12345u, a.line()));
  assert(equal("Custom error", a.failure_message()));
}

TEST("reverse passed assertion") {
  Copper::AssertionResult ar;
  ar.pass();
  Copper::AssertionResult reversed_ar = failed(ar);

  assert(!reversed_ar.passed());
  assert(equal("Unexpected success of assertion 'ar'",
    reversed_ar.failure_message()));
}

TEST("reverse failed assertion") {
  Copper::AssertionResult ar;
  ar.fail("");
  Copper::AssertionResult reversed_ar = failed(ar);

  assert(reversed_ar.passed());
}

}
