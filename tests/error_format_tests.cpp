/* error_format_tests.cpp -- Test behaviour of the error_format () function
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>

using Copper::error_format;

TEST_SUITE (error_format_tests)
{
	TEST (integer)
	{
		ASSERT (equal ("1", error_format (1)));
	}

	TEST (string)
	{
		ASSERT (equal ("\"a\"", error_format ("a")));
	}

	TEST (character)
	{
		ASSERT (equal ("'a'", error_format ('a')));
	}

	TEST (integer_and_join)
	{
		ASSERT (equal ("1 test", error_format (1, "test")));
	}

	TEST (string_and_join)
	{
		ASSERT (equal ("\"a\" test", error_format ("a", "test")));
	}

	TEST (integers)
	{
		ASSERT (equal ("1 test 2", error_format (1, "test", 2)));
	}

	TEST (strings)
	{
		ASSERT (equal ("\"a\" test \"b\"",
		               error_format ("a", "test", "b")));
	}
}
