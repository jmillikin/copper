/* string_tests.cpp - Tests of equal () and unequal () on strings
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>

TEST_SUITE (string_tests)
{
	TEST (construct_with_size)
	{
		Copper::String a ("test", 3), b ("test", 5);
		ASSERT (equal ("tes", a));
		ASSERT (equal ("test", b));
	}

	FIXTURE (str_fixture)
	{
		const Copper::String
			var1 = "test",
			var2 = "test",
			var3 = "other",
			var4 = "other";
		char *cvar1, *cvar2, *cvar3, *cvar4;

		SET_UP {
			cvar1 = Copper::strndup (var1.c_str());
			cvar2 = Copper::strndup (var2.c_str());
			cvar3 = Copper::strndup (var3.c_str());
			cvar4 = Copper::strndup (var4.c_str());
		}

		TEAR_DOWN {
			delete cvar1;
			delete cvar2;
			delete cvar3;
			delete cvar4;
		}
	}

	FIXTURE_TEST (Copper_String_equal, str_fixture)
	{
		ASSERT (equal (var1, var2));
	}

	FIXTURE_TEST (Copper_String_equal_fail, str_fixture)
	{
		ASSERT (failed (equal (var1, var3)));
	}

	FIXTURE_TEST (char_star_equal, str_fixture)
	{
		// Confirm that the addresses are not being compared
		ASSERT (cvar1 != cvar2);

		ASSERT (equal ("test", "test"));
		ASSERT (equal (cvar1, "test"));
		ASSERT (equal (cvar1, cvar2));
	}

	FIXTURE_TEST (char_star_equal_fail, str_fixture)
	{
		ASSERT (failed (equal (cvar1, cvar3)));
	}

	FIXTURE_TEST (mixed_string_equality, str_fixture)
	{
		ASSERT (equal (var1, cvar1));
		ASSERT (equal (var2, cvar1));
	}

	FIXTURE_TEST (mixed_string_equality_fail, str_fixture)
	{
		ASSERT (failed (equal (var1, cvar3)));
	}

	FIXTURE_TEST (Copper_String_unequal, str_fixture)
	{
		ASSERT (unequal (var1, var3));
	}

	FIXTURE_TEST (Copper_String_unequal_fail, str_fixture)
	{
		ASSERT (failed (unequal (var3, var4)));
	}

	FIXTURE_TEST (char_star_unequal, str_fixture) {
		ASSERT (unequal ("test", "other"));
		ASSERT (unequal (cvar1, "other"));
		ASSERT (unequal (cvar1, cvar3));
	}

	FIXTURE_TEST (char_star_unequal_fail, str_fixture)
	{
		ASSERT (failed (unequal (cvar3, cvar4)));
	}

	FIXTURE_TEST (mixed_string_inequality, str_fixture)
	{
		ASSERT (unequal (var1, cvar3));
	}

	FIXTURE_TEST (mixed_string_inequality_fail, str_fixture)
	{
		ASSERT (failed (unequal (var1, cvar2)));
	}

	TEST (compare_to_NULL)
	{
		ASSERT (unequal ("test", (char *)0));
		ASSERT (failed (equal ("test", (char *)0)));
	}
}
