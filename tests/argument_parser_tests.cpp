/* argument_parser_tests.cpp -- Test the commandline argument parser
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/OutputHandler.hpp>
#include <copper.hpp>
#include <cstdio>

typedef Copper::List<Copper::Test> TestList;

TestList *
parse_test_args (int argc, char* argv[])
{
	return Copper::OutputHandler::parse_test_args (argc, argv);
}

// Test the argument parser
SUITE (argument_parser_tests)
{
	TEST (no_arguments)
	{
		int argc = 0;
		char argv_0[] = "";
		char *argv[] = {argv_0};
		TestList *tests = parse_test_args (argc, argv);

		ASSERT (equal (Copper::Test::all ().size (), tests->size ()));
		delete tests;
	}

	TEST (entire_suite)
	{
		int argc = 1;
		char argv_0[] = "argument_parser_tests";
		char *argv[] = {argv_0};
		TestList *tests = parse_test_args (argc, argv);

		ASSERT (equal (7u, tests->size ()));
		delete tests;
	}

	TEST (single_test)
	{
		int argc = 1;
		char argv_0[] = "argument_parser_tests.single_test";
		char *argv[] = {argv_0};
		TestList *tests = parse_test_args (argc, argv);

		ASSERT (equal (1u, tests->size ()));
		delete tests;
	}

	TEST (multiple_tests)
	{
		int argc = 2;
		char argv_0[] = "argument_parser_tests.single_test";
		char argv_1[] = "argument_parser_tests.multiple_tests";
		char *argv[] = {argv_0, argv_1};
		TestList *tests = parse_test_args (argc, argv);

		ASSERT (equal (2u, tests->size ()));
		delete tests;
	}

	TEST (invalid_suite)
	{
		int argc = 1;
		char argv_0[] = "nonexistant_suite";
		char *argv[] = {argv_0};
		TestList *tests = parse_test_args (argc, argv);

		ASSERT (equal (Copper::Test::all ().size (), tests->size ()));
		delete tests;
	}

	TEST (invalid_test)
	{
		int argc = 1;
		char argv_0[] = "argument_parser_tests.nonexistant_test";
		char *argv[] = {argv_0};
		TestList *tests = parse_test_args (argc, argv);

		ASSERT (equal (Copper::Test::all ().size (), tests->size ()));
		delete tests;
	}

	TEST (mixed_valid_and_invalid)
	{
		int argc = 2;
		char argv_0[] = "argument_parser_tests.single_test";
		char argv_1[] = "argument_parser_tests.nonexistant_test";
		char *argv[] = {argv_0, argv_1};
		TestList *tests = parse_test_args (argc, argv);

		ASSERT (equal (1u, tests->size ()));
		delete tests;
	}
}
