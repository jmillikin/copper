/* full_self_tests.cpp -- Tests that may cause false negatives, but are
 *   useful for testing the framework
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "test.hpp"
#include "fixture.hpp"
#include "error_exception.hpp"

// Perform full testing of the framework, including error handling
// This isn't usually included, since it can cause false errors for otherwise
// fine programs

TEST_SUITE(full_self_tests) {

TEST(error_exception) {
  throw UnitTests::ErrorException("self-thrown ErrorException");
}

TEST(unexpected_exceptions) {
  throw 0;
}

}
