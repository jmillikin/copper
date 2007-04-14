/* sample_suite.cpp -- Samples for learning the framework
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>

TEST_SUITE (sample_suite)
{
	TEST (equality)
	{
		// Equality is performed with the 'equal' function. Equality
		// works with any two types that can be passed to ==
		ASSERT (equal (2, 2));

		// Equality also works with C-style strings
		ASSERT (equal ("test", "test"));
	}

	TEST (near_equality)
	{
		// Equal within is used for floating point numbers, where
		// exactness might not be possible (though it can take any
		// type with >, < and + operators
		ASSERT (equal_within (2.0, 2.0001, 0.001));
	}

	TEST (inequality)
	{
		// Assert that two values are not equal
		ASSERT (unequal (1, 2));
	}

	TEST (is_NULL)
	{
		// Used to check that some pointer is NULL
		int *var = NULL;
		ASSERT (null (var));
	}

	TEST (is_not_NULL)
	{
		// Used to check that some pointer is not NULL
		int var;
		ASSERT (not_null (&var));
	}

	TEST (greater_than)
	{
		// Assert some value is > another value
		ASSERT (greater_than (2, 1));
	}

	TEST (greater_than_or_equal)
	{
		// Assert some value is >= another value
		ASSERT (greater_than_or_equal (2, 2));
		ASSERT (greater_than_or_equal (2, 1));
	}

	TEST (less_than)
	{
		// Assert some value is < another value
		ASSERT (less_than (1, 2));
	}

	TEST (less_than_or_equal)
	{
		// Assert some value is <= another value
		ASSERT (less_than_or_equal (1, 2));
		ASSERT (less_than_or_equal (2, 2));
	}

	// Fixtures are used for multiple tests that should use the same data.
	// Fixture data is automatically available on the stack, though it
	// should be initialized in SET_UP to avoid dirty data shared between
	// tests using the same fixture. Dynamically allocated memory or
	// opened files should be closed in TEAR_DOWN, if needed.
	FIXTURE (the_fixture)
	{
		int fixture_var = 0;
		bool set_up_finished = false;

		SET_UP {
			fixture_var = 1;
			set_up_finished = true;
		}
	}

	FIXTURE_TEST (test_with_a_fixture, the_fixture)
	{
		ASSERT (equal (fixture_var, 1));
		ASSERT (set_up_finished);
	}

	// Some systems also support catching various programming errors

	TEST (NULL_pointer_dereference)
	{
		int *i = 0;
		*i = 1;
	}

	TEST (division_by_zero)
	{
		int i = 1 / 0;
	}
}
