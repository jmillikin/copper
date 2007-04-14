/* argument_parser_tests.cpp -- Test the commandline argument parser
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/output_handler.hpp>
#include <copper.hpp>
#include <cstdio>

typedef Copper::List<Copper::Test> TestList;

TestList
parse_test_args (int argc, char** argv)
{
	return Copper::OutputHandler::parse_test_args (argc, argv);
}

// Test the argument parser
TEST_SUITE (argument_parser_tests)
{
	TEST (no_arguments)
	{
		int argc = 0;
		char *argv[] = {""};
		TestList tests = parse_test_args (argc, argv);

		ASSERT (equal (Copper::Test::all ().size (), tests.size ()));
	}

	TEST (entire_suite)
	{
		int argc = 1;
		char *argv[] = {"argument_parser_tests"};
		TestList tests = parse_test_args (argc, argv);

		ASSERT (equal (current_suite.get_tests ().size (),
		              tests.size ()));
	}

	TEST (single_test)
	{
		int argc = 1;
		char *argv[] = {"argument_parser_tests.single_test"};
		TestList tests = parse_test_args (argc, argv);

		ASSERT (equal (1, tests.size ()));
	}

	TEST (multiple_tests)
	{
		int argc = 2;
		char *argv[] = {
			"argument_parser_tests.single_test",
			"argument_parser_tests.multiple_tests",
		};
		TestList tests = parse_test_args (argc, argv);

		ASSERT (equal (2, tests.size ()));
	}

	TEST (invalid_suite)
	{
		int argc = 1;
		char *argv[] = {"nonexistant_suite"};
		TestList tests = parse_test_args (argc, argv);

		ASSERT (equal (Copper::Test::all ().size (), tests.size ()));
	}

	TEST (invalid_test)
	{
		int argc = 1;
		char *argv[] = {"argument_parser_tests.nonexistant_test"};
		TestList tests = parse_test_args (argc, argv);

		ASSERT (equal (Copper::Test::all ().size (), tests.size ()));
	}

	TEST (mixed_valid_and_invalid)
	{
		int argc = 2;
		char *argv[] = {
			"argument_parser_tests.single_test",
			"argument_parser_tests.nonexistant_test",
		};
		TestList tests = parse_test_args (argc, argv);

		ASSERT (equal (1, tests.size ()));
	}
}
