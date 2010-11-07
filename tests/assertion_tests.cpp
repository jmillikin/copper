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
#include <cstring>
#include <cstdlib>

COPPER_SUITE(assertion)
{

COPPER_TEST(boolean_true)
{
	COPPER_ASSERT(true);
}

COPPER_TEST(COPPER_ASSERT_failed)
{
	// Check that a failed test will result in a pass
	COPPER_ASSERT(failed(false));
}

COPPER_TEST(COPPER_ASSERT_failed_fail)
{
	// Check that a passing test will result in a fail
	COPPER_ASSERT(failed(failed(true)));
}

COPPER_TEST(integer_equals)
{
	COPPER_ASSERT(equal(2, 2));
}

COPPER_TEST(integer_equals_fail)
{
	COPPER_ASSERT(failed(equal(1, 2)));
}

COPPER_TEST(equal_within)
{
	COPPER_ASSERT(equal_within(2.0, 2.0001, 0.001));
}

COPPER_TEST(equal_within_fail)
{
	COPPER_ASSERT(failed(equal_within(2.0, 2.01, 0.001)));
}

COPPER_TEST(unequal)
{
	COPPER_ASSERT(unequal(1, 2));
}

COPPER_TEST(unequal_fail)
{
	COPPER_ASSERT(failed(unequal(2, 2)));
}

COPPER_TEST(is_null)
{
	int *var = NULL;
	COPPER_ASSERT(is_null(var));
}

COPPER_TEST(is_null_fail)
{
	int var;
	COPPER_ASSERT(failed(is_null(&var)));
}

COPPER_TEST(not_null)
{
	int var;
	COPPER_ASSERT(not_null(&var));
}

COPPER_TEST(not_null_fail)
{
	int *var = NULL;
	COPPER_ASSERT(failed(not_null(var)));
}

COPPER_TEST(greater_than)
{
	COPPER_ASSERT(greater_than(2, 1));
}

COPPER_TEST(greater_than_fail)
{
	COPPER_ASSERT(failed(greater_than(2, 2)));
	COPPER_ASSERT(failed(greater_than(2, 3)));
}

COPPER_TEST(greater_than_or_equal)
{
	COPPER_ASSERT(greater_than_or_equal(2, 2));
	COPPER_ASSERT(greater_than_or_equal(2, 1));
}

COPPER_TEST(greater_than_or_equal_fail)
{
	COPPER_ASSERT(failed(greater_than_or_equal(1, 2)));
}

COPPER_TEST(less_than)
{
	COPPER_ASSERT(less_than(1, 2));
}

COPPER_TEST(less_than_fail)
{
	COPPER_ASSERT(failed(less_than(2, 2)));
	COPPER_ASSERT(failed(less_than(2, 1)));
}

COPPER_TEST(less_than_or_equal)
{
	COPPER_ASSERT(less_than_or_equal(1, 2));
	COPPER_ASSERT(less_than_or_equal(2, 2));
}

COPPER_TEST(less_than_or_equal_fail)
{
	COPPER_ASSERT(failed(less_than_or_equal(2, 1)));
}

COPPER_TEST(not_operator)
{
	COPPER_ASSERT(!equal(1, 2));
	COPPER_ASSERT(failed(!equal(1, 1)));
}

COPPER_TEST(and_operator)
{
	COPPER_ASSERT(   equal(1, 1) &&  equal(1, 1));
	COPPER_ASSERT(!(!equal(1, 1) &&  equal(1, 1)));
	COPPER_ASSERT(!( equal(1, 1) && !equal(1, 1)));
	COPPER_ASSERT(!(!equal(1, 1) && !equal(1, 1)));
}

COPPER_TEST(or_operator)
{
	COPPER_ASSERT(   equal(1, 1) ||  equal(1, 1));
	COPPER_ASSERT(  !equal(1, 1) ||  equal(1, 1));
	COPPER_ASSERT(   equal(1, 1) || !equal(1, 1));
	COPPER_ASSERT(!(!equal(1, 1) || !equal(1, 1)));
}

COPPER_TEST(and_operator_booleans)
{
	COPPER_ASSERT(true && equal(1, 1));
	COPPER_ASSERT(equal(1, 1) && true);
	
	COPPER_ASSERT(!(true && equal(1, 2)));
	COPPER_ASSERT(!(equal(1, 1) &&  false));
	
	COPPER_ASSERT(!(false && equal(1, 1)));
	COPPER_ASSERT(!(equal(1, 2) && false));
}

COPPER_TEST(or_operator_booleans)
{
	COPPER_ASSERT(true || equal(1, 1));
	COPPER_ASSERT(equal(1, 1) || true);
	
	COPPER_ASSERT(true || equal(1, 2));
	COPPER_ASSERT(equal(1, 2) || true);
	
	COPPER_ASSERT(false || equal(1, 1));
	COPPER_ASSERT(equal(1, 1) || false);
}

}
