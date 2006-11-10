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

FIXTURE(str_fixture) {
  const Copper::String
    var1 = "test",
    var2 = "test",
    var3 = "other",
    var4 = "other";
  char* cvar1, *cvar2, *cvar3, *cvar4;
  void set_up() {
    cvar1 = Copper::strdup(var1.c_str());
    cvar2 = Copper::strdup(var2.c_str());
    cvar3 = Copper::strdup(var3.c_str());
    cvar4 = Copper::strdup(var4.c_str());
  }

  void tear_down() {
    std::free(cvar1);
    std::free(cvar2);
    std::free(cvar3);
    std::free(cvar4);
  }
}

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

FIXTURE(the_fixture) {
  int fixture_var = 0;
  bool set_up_finished = false;

  void set_up(){
    fixture_var = 1;
    set_up_finished = true;
  }

  void tear_down() {}
}

FIXTURE_TEST(fixture_test, the_fixture) {
  assert(equal(fixture_var, 1));
  assert(set_up_finished);
}

// Used to create pretty names to show the user
TEST(pretty_names) {
  Copper::String name;

  // Basic capitalization
  name = Copper::OutputHandler::pretty_name("something");
  assert(equal("Something", name));

  // Underscore conversion
  name = Copper::OutputHandler::pretty_name("some_thing");
  assert(equal("Some thing", name));

  // Leaves capitals alone
  name = Copper::OutputHandler::pretty_name("Something");
  assert(equal("Something", name));
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

class self_test_fail : public Copper::Test {
public:
  self_test_fail(): Copper::Test("fail self test", NULL, __FILE__){}
  void _run(Copper::Assertion** bad_assertion) {
    assert(false);
  }
protected:
  void set_up(){}
  void tear_down(){}
};

TEST(failed_test__run) {
  self_test_fail self_test_instance;

  Copper::Assertion* failed = 0;
  self_test_instance._run(&failed);
  assert(not_null(failed));
  delete failed;
}

class self_test_pass : public Copper::Test {
public:
  self_test_pass(): Copper::Test("pass self test", NULL, __FILE__){}
  void _run(Copper::Assertion** bad_assertion) {
    assert(true);
  }
protected:
  void set_up(){}
  void tear_down(){}
};

TEST(successful_test__run) {
  self_test_pass self_test_instance;

  Copper::Assertion* failed = 0;
  self_test_instance._run(&failed);
  assert(null(failed));
}

#if ENABLE_VARIADIC_ASSERT == 1
class self_test_fail_custom_error : public Copper::Test {
public:
  self_test_fail_custom_error(): Copper::Test(
    "fail self test with custom error", NULL, __FILE__){}
  void _run(Copper::Assertion** bad_assertion) {
    assert(false, "Custom error string");
  }
protected:
  void set_up(){}
  void tear_down(){}
};

TEST(fail_with_custom_error) {
  self_test_fail_custom_error self_test_instance;

  Copper::Assertion* failed = 0;
  self_test_instance._run(&failed);
  assert(not_null(failed));

  assert(equal("Custom error string", failed->failure_message()));

  delete failed;
}
#endif /* ENABLE_VARIADIC_ASSERT */

// Re-include macros.hpp to define fail()
#undef COPPER_MACROS_HPP
#include <copper/macros.hpp>

class self_test_explicit_fail : public Copper::Test {
public:
  self_test_explicit_fail(): Copper::Test( "", NULL, __FILE__){}
  void _run(Copper::Assertion** bad_assertion) {
    fail("Custom failure string");
  }
protected:
  void set_up(){}
  void tear_down(){}
};

TEST(explicit_fail) {
  self_test_explicit_fail self_test_instance;

  Copper::Assertion* failed;
  self_test_instance._run(&failed);
  assert(not_null(failed));

  assert(equal("Custom failure string", failed->failure_message()));

  delete failed;
}

}
