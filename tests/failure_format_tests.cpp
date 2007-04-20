/* failure_format_tests.cpp -- Test behaviour of the failure_format () function
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>

using Copper::failure_format;

TEST_SUITE (failure_format_tests)
{
	TEST (integer)
	{
		ASSERT (equal ("1", failure_format (1)));
	}

	TEST (string)
	{
		ASSERT (equal ("\"a\"", failure_format ("a")));
	}

	TEST (null_string)
	{
		char *a = 0;
		const char *b = 0;
		ASSERT (equal ("NULL", failure_format (a)));
		ASSERT (equal ("NULL", failure_format (b)));
	}

	TEST (character)
	{
		ASSERT (equal ("'a'", failure_format ('a')));
	}

	TEST (integer_and_join)
	{
		ASSERT (equal ("1 test", failure_format (1, "test")));
	}

	TEST (string_and_join)
	{
		ASSERT (equal ("\"a\" test", failure_format ("a", "test")));
	}

	TEST (integers)
	{
		ASSERT (equal ("1 test 2", failure_format (1, "test", 2)));
	}

	TEST (strings)
	{
		ASSERT (equal ("\"a\" test \"b\"",
		               failure_format ("a", "test", "b")));
	}
}