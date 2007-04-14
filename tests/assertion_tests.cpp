/* assertion_tests.cpp - Testing of each assertion function
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>
#include <cstring>
#include <cstdlib>

TEST_SUITE(assertion_tests) {

TEST(boolean_true) {
  ASSERT(true);
}

TEST(ASSERT_failed) {
  // Check that a failed test will result in a pass
  ASSERT(failed(false));
}

TEST(ASSERT_failed_fail) {
  // Check that a passing test will result in a fail
  ASSERT(failed(failed(true)));
}

TEST(integer_equals) {
  ASSERT(equal(2, 2));
}

TEST(integer_equals_fail) {
  ASSERT(failed(equal(1, 2)));
}

TEST(equal_within) {
  ASSERT(equal_within(2.0, 2.0001, 0.001));
}

TEST(equal_within_fail) {
  ASSERT(failed(equal_within(2.0, 2.01, 0.001)));
}

TEST(unequal) {
  ASSERT(unequal(1, 2));
}

TEST(unequal_fail) {
  ASSERT(failed(unequal(2, 2)));
}

TEST(is_null) {
  int* var = 0;
  ASSERT(null(var));
}

TEST(is_null_fail) {
  int var;
  ASSERT(failed(null(&var)));
}

TEST(not_null) {
  int var;
  ASSERT(not_null(&var));
}

TEST(not_null_fail) {
  int* var = 0;
  ASSERT(failed(not_null(var)));
}

TEST(greater_than) {
  ASSERT(greater_than(2, 1));
}

TEST(greater_than_fail) {
  ASSERT(failed(greater_than(2, 2)));
  ASSERT(failed(greater_than(2, 3)));
}

TEST(greater_than_or_equal) {
  ASSERT(greater_than_or_equal(2, 2));
  ASSERT(greater_than_or_equal(2, 1));
}

TEST(greater_than_or_equal_fail) {
  ASSERT(failed(greater_than_or_equal(1, 2)));
}

TEST(less_than) {
  ASSERT(less_than(1, 2));
}

TEST(less_than_fail) {
  ASSERT(failed(less_than(2, 2)));
  ASSERT(failed(less_than(2, 1)));
}

TEST(less_than_or_equal) {
  ASSERT(less_than_or_equal(1, 2));
  ASSERT(less_than_or_equal(2, 2));
}

TEST(less_than_or_equal_fail) {
  ASSERT(failed(less_than_or_equal(2, 1)));
}
/*
TEST(ASSERT_throws) {
  ASSERT(throws(int, throw 0));
}*/

}
