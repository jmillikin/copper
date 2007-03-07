/* argument_parser_tests.cpp - Test the commandline argument parser
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper/output_handler.hpp>
#include <copper.hpp>

// Test the argument parser
TEST_SUITE(argument_parser_tests) {

TEST(no_arguments) {
  Copper::List<Copper::Test> tests;
  int argc = 0;
  char* argv[] = {};
}

}
