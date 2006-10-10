/* self_tests.cpp - Various self-tests of the framework
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "../src/test.hpp"
#include "../src/fixture.hpp"
#include "../src/output_handler.hpp"
#include "../src/macros.hpp"

// Various self-tests of the framework, to try and avoid bugs
TEST_SUITE(self_tests) {

TEST(boolean_true) {
  assert(true);
}

TEST(assert_failed) {
  // Check that a failed test will result in a pass
  assert(failed(false));
}

TEST(assert_failed_fail) {
  // Check that a passing test will result in a fail
  assert(failed(failed(true)));
}

TEST(integer_equals) {
  assert(equal(2, 2));
}

TEST(integer_equals_fail) {
  assert(failed(equal(1, 2)));
}

FIXTURE(str_fixture)
  std::string var1, var2, var3, var4;
  const char* cvar1, *cvar2, *cvar3, *cvar4;
  void set_up() {
    var1 = "test";
    var2 = "test";
    var3 = "other";
    var4 = "other";
    cvar1 = var1.c_str();
    cvar2 = var2.c_str();
    cvar3 = var3.c_str();
    cvar4 = var4.c_str();
  }
};

FIXTURE_TEST(std_string_equal, str_fixture) {
  assert(equal(var1, var2));
}

FIXTURE_TEST(std_string_equal_fail, str_fixture) {
  assert(failed(equal(var1, var3)));
}

FIXTURE_TEST(char_string_equal, str_fixture) {
  // Confirm that the addresses are not being compared
  assert(cvar1 != cvar2);

  assert(equal("test", "test"));
  assert(equal(cvar1, "test"));
  assert(equal(cvar1, cvar2));
}

FIXTURE_TEST(char_string_equal_fail, str_fixture) {
  assert(failed(equal(cvar1, cvar3)));
}

FIXTURE_TEST(mixed_string_equality, str_fixture) {
  assert(equal(var1, cvar1));
  assert(equal(var2, cvar1));
}

FIXTURE_TEST(mixed_string_equality_fail, str_fixture) {
  assert(failed(equal(var1, cvar3)));
}

FIXTURE_TEST(std_string_unequal, str_fixture) {
  assert(unequal(var1, var3));
}

FIXTURE_TEST(std_string_unequal_fail, str_fixture) {
  assert(failed(unequal(var3, var4)));
}

FIXTURE_TEST(char_string_unequal, str_fixture) {
  assert(unequal("test", "other"));
  assert(unequal(cvar1, "other"));
  assert(unequal(cvar1, cvar3));
}

FIXTURE_TEST(char_string_unequal_fail, str_fixture) {
  assert(failed(unequal(cvar3, cvar4)));
}

FIXTURE_TEST(mixed_string_inequality, str_fixture) {
  assert(unequal(var1, cvar3));
}

FIXTURE_TEST(mixed_string_inequality_fail, str_fixture) {
  assert(failed(unequal(var1, cvar2)));
}

TEST(equal_within) {
  assert(equal_within(2.0, 2.0001, 0.001));
}

TEST(equal_within_fail) {
  assert(failed(equal_within(2.0, 2.01, 0.001)));
}

TEST(unequal) {
  assert(unequal(1, 2));
}

TEST(unequal_fail) {
  assert(failed(unequal(2, 2)));
}

TEST(is_null) {
  int* var = 0;
  assert(null(var));
}

TEST(is_null_fail) {
  int var;
  assert(failed(null(&var)));
}

TEST(not_null) {
  int var;
  assert(not_null(&var));
}

TEST(not_null_fail) {
  int* var = 0;
  assert(failed(not_null(var)));
}

TEST(greater_than) {
  assert(greater_than(2, 1));
}

TEST(greater_than_fail) {
  assert(failed(greater_than(2, 2)));
  assert(failed(greater_than(2, 3)));
}

TEST(greater_than_or_equal) {
  assert(greater_than_or_equal(2, 2));
  assert(greater_than_or_equal(2, 1));
}

TEST(greater_than_or_equal_fail) {
  assert(failed(greater_than_or_equal(1, 2)));
}

TEST(less_than) {
  assert(less_than(1, 2));
}

TEST(less_than_fail) {
  assert(failed(less_than(2, 2)));
  assert(failed(less_than(2, 1)));
}

TEST(less_than_or_equal) {
  assert(less_than_or_equal(1, 2));
  assert(less_than_or_equal(2, 2));
}

TEST(less_than_or_equal_fail) {
  assert(failed(less_than_or_equal(2, 1)));
}

#ifndef NO_EXCEPTIONS
TEST(thrown_exception) {
  assert_throws(throw 0, int);
}
#endif

// Currently no way to test this
/*
TEST(thrown_exception_fail) {
  assert(failed(assert_throws(true, int)));
}
*/

FIXTURE(the_fixture)
  void set_up(){
    fixture_var = 1;
    set_up_finished = true;
  }

  // If desired, include a "void tear_down(){..."

  int fixture_var;
  bool set_up_finished;
};

FIXTURE_TEST(fixture_test, the_fixture) {
  assert(equal(fixture_var, 1));
  assert(set_up_finished);
}

// Used to create pretty names to show the user
TEST(pretty_names) {
  // Basic capitalization
  assert(equal(UnitTests::OutputHandler::pretty_name("something"),
    "Something"));

  // Underscore conversion
  assert(equal(UnitTests::OutputHandler::pretty_name("some_thing"),
    "Some thing"));

  // Leaves capitals alone
  assert(equal(UnitTests::OutputHandler::pretty_name("Something"),
    "Something"));
}

// Tests of implementation details

TEST(assertion_result_fresh) {
  UnitTests::AssertionResult ar;
  assert(!ar.passed());
  assert(equal(ar.failure_message(), "Unitialized AssertionResult"));
}

TEST(assertion_result_pass) {
  UnitTests::AssertionResult ar;
  ar.pass();

  assert(ar.passed());
  assert(equal(ar.failure_message(), "No Error"));

  ar.fail("Bad fail");
  assert(ar.passed());
  assert(equal(ar.failure_message(), "No Error"));
}

TEST(assertion_result_failure) {
  UnitTests::AssertionResult ar;
  ar.fail("Error goes here");

  assert(!ar.passed());
  assert(equal(ar.failure_message(), "Error goes here"));

  ar.pass();
  assert(!ar.passed());
  assert(equal(ar.failure_message(), "Error goes here"));
}

TEST(boolean_assertion_pass) {
  UnitTests::AssertionResult ar(true);

  assert(ar.passed());
}

TEST(boolean_assertion_failure) {
  UnitTests::AssertionResult ar(false);

  assert(!ar.passed());
  assert(equal(ar.failure_message(), "Boolean assertion failed"));
}

TEST(assertion_pass) {
  UnitTests::AssertionResult ar;
  ar.pass();
  UnitTests::Assertion a(ar, "Assertion text", 12345);

  assert(a.passed());
  assert(equal(a.text(), "Assertion text"));
  assert(equal(a.line(), 12345u));
}

TEST(assertion_failure) {
  UnitTests::AssertionResult ar;
  ar.fail("Error goes here");
  UnitTests::Assertion a(ar, "Assertion text", 12345);

  assert(!a.passed());
  assert(equal(a.text(), "Assertion text"));
  assert(equal(a.line(), 12345u));
  assert(equal(a.failure_message(), "Error goes here"));
}

TEST(reverse_passed_assertion) {
  UnitTests::AssertionResult ar;
  ar.pass();
  UnitTests::AssertionResult reversed_ar = failed(ar);

  assert(!reversed_ar.passed());
  assert(equal("Unexpected success of assertion 'ar'",
    reversed_ar.failure_message()));
}

TEST(reverse_failed_assertion) {
  UnitTests::AssertionResult ar;
  ar.fail("");
  UnitTests::AssertionResult reversed_ar = failed(ar);

  assert(reversed_ar.passed());
}

class self_test_fail : public UnitTests::Test {
public:
  self_test_fail(): UnitTests::Test("fail self test", &current_suite,
    __FILE__){}
  void _run(UnitTests::Assertion** bad_assertion) {
    assert(false);
  }
protected:
  void set_up(){}
  void tear_down(){}
};

TEST(failed_test__run) {
  self_test_fail self_test_instance;

  UnitTests::Assertion* failed;
  self_test_instance._run(&failed);
  assert(not_null(failed));
  delete failed;
}

class self_test_pass : public UnitTests::Test {
public:
  self_test_pass(): UnitTests::Test("pass self test", &current_suite,
    __FILE__){}
  void _run(UnitTests::Assertion** bad_assertion) {
    assert(true);
  }
protected:
  void set_up(){}
  void tear_down(){}
};

TEST(successful_test__run) {
  self_test_pass self_test_instance;

  UnitTests::Assertion* failed = 0;
  self_test_instance._run(&failed);
  assert(null(failed));
}

}
