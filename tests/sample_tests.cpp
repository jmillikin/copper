// Copyright (C) 2006-2010 John Millikin <jmillikin@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <copper.hpp>

COPPER_SUITE(sample_suite)
{

COPPER_TEST(equality)
{
	// Equality is performed with the 'equal' function. Equality
	// works with any two types that can be passed to ==
	COPPER_ASSERT(equal(2, 2));
	
	// Equality also works with C-style strings
	COPPER_ASSERT(equal("test", "test"));
}

COPPER_TEST(near_equality)
{
	// Equal within is used for floating point numbers, where
	// exactness might not be possible(though it can take any
	// type with >, < and + operators
	COPPER_ASSERT(equal_within(2.0, 2.0001, 0.001));
}

COPPER_TEST(inequality)
{
	// Assert that two values are not equal
	COPPER_ASSERT(unequal(1, 2));
}

COPPER_TEST(is_NULL)
{
	// Used to check that some pointer is NULL
	int *var = NULL;
	COPPER_ASSERT(is_null(var));
}

COPPER_TEST(is_not_NULL)
{
	// Used to check that some pointer is not NULL
	int var;
	COPPER_ASSERT(not_null(&var));
}

COPPER_TEST(greater_than)
{
	// Assert some value is > another value
	COPPER_ASSERT(greater_than(2, 1));
}

COPPER_TEST(greater_than_or_equal)
{
	// Assert some value is >= another value
	COPPER_ASSERT(greater_than_or_equal(2, 2));
	COPPER_ASSERT(greater_than_or_equal(2, 1));
}

COPPER_TEST(less_than)
{
	// Assert some value is < another value
	COPPER_ASSERT(less_than(1, 2));
}

COPPER_TEST(less_than_or_equal)
{
	// Assert some value is <= another value
	COPPER_ASSERT(less_than_or_equal(1, 2));
	COPPER_ASSERT(less_than_or_equal(2, 2));
}

// Fixtures are used for multiple tests that should use the same data.
// Fixture data is automatically available on the stack, though it
// might need to be initialized in COPPER_SET_UP. Dynamically
// allocated memory or opened files should be closed inCOPPER_TEAR_DOWN,
// if needed.
COPPER_FIXTURE(the_fixture)
{
	int fixture_var;
	bool set_up_finished;
	
	COPPER_SET_UP {
		fixture_var = 1;
		set_up_finished = true;
	}
};

COPPER_FIXTURE_TEST(test_with_a_fixture, the_fixture)
{
	COPPER_ASSERT(equal(fixture_var, 1));
	COPPER_ASSERT(set_up_finished);
}

// Failures occur when an assertion's condition is not met

COPPER_TEST(assertion_failure)
{
	COPPER_ASSERT(equal("the answer", "42"));
}

// Some systems also support catching various programming errors

COPPER_TEST(NULL_pointer_dereference)
{
	int *i = 0;
	*i = 1;
}

COPPER_TEST(division_by_zero)
{
	int i = 1 / 0;
}

}
