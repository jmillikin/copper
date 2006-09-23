#include "test.h"
#include "fixture.h"

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
  std::string var1, var2, var3;
  const char* cvar1, *cvar2, *cvar3;
  void set_up() {
    var1 = "test";
    var2 = "test";
    var3 = "other";
    cvar1 = var1.c_str();
    cvar2 = var2.c_str();
    cvar3 = var3.c_str();
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

TEST(thrown_exception) {
  assert_throws(throw 0, int);
}

TEST(thrown_exception_fail) {
  // Standard assert(failed(...)) doesn't work for freaky macros
  assert_throws(assert_throws(true, int),
    UnitTests::FailureException);
}

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

}
