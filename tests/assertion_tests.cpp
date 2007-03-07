/* assertion_tests.cpp - Testing of each assertion function
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper.hpp>
#include <cstring>
#include <cstdlib>

TEST_SUITE(assertion_tests) {

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

}
