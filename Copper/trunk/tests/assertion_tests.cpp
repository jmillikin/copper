/* assertion_tests.cpp - Testing of each assertion function
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper.hpp>
#include <cstring>
#include <cstdlib>

TEST_SUITE("Assertion tests") {

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

}
