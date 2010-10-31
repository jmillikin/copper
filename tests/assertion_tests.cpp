/* assertion_tests.cpp -- Testing of each assertion function
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>
#include <cstring>
#include <cstdlib>

COPPER_SUITE (assertion_tests)
{
	COPPER_TEST (boolean_true)
	{
		COPPER_ASSERT (true);
	}

	COPPER_TEST (COPPER_ASSERT_failed)
	{
		// Check that a failed test will result in a pass
		COPPER_ASSERT (failed (false));
	}

	COPPER_TEST (COPPER_ASSERT_failed_fail)
	{
		// Check that a passing test will result in a fail
		COPPER_ASSERT (failed (failed (true)));
	}

	COPPER_TEST (integer_equals)
	{
		COPPER_ASSERT (equal (2, 2));
	}

	COPPER_TEST (integer_equals_fail)
	{
		COPPER_ASSERT (failed (equal (1, 2)));
	}

	COPPER_TEST (equal_within)
	{
		COPPER_ASSERT (equal_within (2.0, 2.0001, 0.001));
	}

	COPPER_TEST (equal_within_fail)
	{
		COPPER_ASSERT (failed (equal_within (2.0, 2.01, 0.001)));
	}

	COPPER_TEST (unequal)
	{
		COPPER_ASSERT (unequal (1, 2));
	}

	COPPER_TEST (unequal_fail)
	{
		COPPER_ASSERT (failed (unequal (2, 2)));
	}

	COPPER_TEST (is_null)
	{
		int *var = NULL;
		COPPER_ASSERT (is_null (var));
	}

	COPPER_TEST (is_null_fail)
	{
		int var;
		COPPER_ASSERT (failed (is_null (&var)));
	}

	COPPER_TEST (not_null)
	{
		int var;
		COPPER_ASSERT (not_null (&var));
	}

	COPPER_TEST (not_null_fail)
	{
		int *var = NULL;
		COPPER_ASSERT (failed (not_null (var)));
	}

	COPPER_TEST (greater_than)
	{
		COPPER_ASSERT (greater_than (2, 1));
	}

	COPPER_TEST (greater_than_fail)
	{
		COPPER_ASSERT (failed (greater_than (2, 2)));
		COPPER_ASSERT (failed (greater_than (2, 3)));
	}

	COPPER_TEST (greater_than_or_equal)
	{
		COPPER_ASSERT (greater_than_or_equal (2, 2));
		COPPER_ASSERT (greater_than_or_equal (2, 1));
	}

	COPPER_TEST (greater_than_or_equal_fail)
	{
		COPPER_ASSERT (failed (greater_than_or_equal (1, 2)));
	}

	COPPER_TEST (less_than)
	{
		COPPER_ASSERT (less_than (1, 2));
	}

	COPPER_TEST (less_than_fail)
	{
		COPPER_ASSERT (failed (less_than (2, 2)));
		COPPER_ASSERT (failed (less_than (2, 1)));
	}

	COPPER_TEST (less_than_or_equal)
	{
		COPPER_ASSERT (less_than_or_equal (1, 2));
		COPPER_ASSERT (less_than_or_equal (2, 2));
	}

	COPPER_TEST (less_than_or_equal_fail)
	{
		COPPER_ASSERT (failed (less_than_or_equal (2, 1)));
	}

	COPPER_TEST (not_operator)
	{
		COPPER_ASSERT (!equal (1, 2));
		COPPER_ASSERT (failed (!equal (1, 1)));
	}

	COPPER_TEST (and_operator)
	{
		COPPER_ASSERT (   equal (1, 1) &&  equal (1, 1));
		COPPER_ASSERT (!(!equal (1, 1) &&  equal (1, 1)));
		COPPER_ASSERT (!( equal (1, 1) && !equal (1, 1)));
		COPPER_ASSERT (!(!equal (1, 1) && !equal (1, 1)));
	}

	COPPER_TEST (or_operator)
	{
		COPPER_ASSERT (   equal (1, 1) ||  equal (1, 1));
		COPPER_ASSERT (  !equal (1, 1) ||  equal (1, 1));
		COPPER_ASSERT (   equal (1, 1) || !equal (1, 1));
		COPPER_ASSERT (!(!equal (1, 1) || !equal (1, 1)));
	}

	COPPER_TEST (and_operator_booleans)
	{
		COPPER_ASSERT (true && equal (1, 1));
		COPPER_ASSERT (equal (1, 1) && true);

		COPPER_ASSERT (!(true && equal (1, 2)));
		COPPER_ASSERT (!(equal (1, 1) &&  false));

		COPPER_ASSERT (!(false && equal (1, 1)));
		COPPER_ASSERT (!(equal (1, 2) && false));
	}

	COPPER_TEST (or_operator_booleans)
	{
		COPPER_ASSERT (true || equal (1, 1));
		COPPER_ASSERT (equal (1, 1) || true);

		COPPER_ASSERT (true || equal (1, 2));
		COPPER_ASSERT (equal (1, 2) || true);

		COPPER_ASSERT (false || equal (1, 1));
		COPPER_ASSERT (equal (1, 1) || false);
	}
}
