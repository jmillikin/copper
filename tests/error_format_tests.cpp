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
		ASSERT (equal ("1 test", error_format (1, "test")));
	}

	TEST (string)
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

	TEST (null)
	{
		ASSERT (equal ("NULL test", error_format (NULL, "test")));
	}

	TEST (nulls)
	{
		ASSERT (equal ("NULL test NULL",
		               error_format (NULL, "test", NULL)));
	}

	TEST (integer_and_null)
	{
		ASSERT (equal ("1 test NULL",
		               error_format (1, "test", NULL)));
	}

	TEST (string_and_null)
	{
		ASSERT (equal ("\"a\" test NULL",
		               error_format ("a", "test", NULL)));
	}
}
