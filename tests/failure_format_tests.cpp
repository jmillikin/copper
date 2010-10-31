/* failure_format_tests.cpp -- Test behaviour of the failure_format () function
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>

#if HAVE_STD_STRING
#	include <string>
#endif

using Copper::failure_format;

COPPER_SUITE (failure_format_tests)
{
	COPPER_TEST (integer)
	{
		COPPER_ASSERT (equal ("1", failure_format (1)));
	}

	COPPER_TEST (string)
	{
		COPPER_ASSERT (equal ("\"a\"", failure_format ("a")));
	}

#if HAVE_STD_STRING
	COPPER_TEST (std_string)
	{
		COPPER_ASSERT (equal ("\"a\"", failure_format (std::string ("a"))));
	}
#endif

	COPPER_TEST (null_string)
	{
		char *a = 0;
		const char *b = 0;
		COPPER_ASSERT (equal ("NULL", failure_format (a)));
		COPPER_ASSERT (equal ("NULL", failure_format (b)));
	}

	COPPER_TEST (character)
	{
		COPPER_ASSERT (equal ("'a'", failure_format ('a')));
	}

	COPPER_TEST (integer_and_join)
	{
		COPPER_ASSERT (equal ("1 test", failure_format (1, "test")));
	}

	COPPER_TEST (string_and_join)
	{
		COPPER_ASSERT (equal ("\"a\" test", failure_format ("a", "test")));
	}

	COPPER_TEST (integers)
	{
		COPPER_ASSERT (equal ("1 test 2", failure_format (1, "test", 2)));
	}

	COPPER_TEST (strings)
	{
		COPPER_ASSERT (equal ("\"a\" test \"b\"",
		               failure_format ("a", "test", "b")));
	}
}
