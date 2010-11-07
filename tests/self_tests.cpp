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

// Various self-tests of the framework, to try and avoid bugs
COPPER_SUITE(self_tests)
{

COPPER_FIXTURE(the_fixture)
{
	int fixture_var;
	bool set_up_finished;
	
	COPPER_SET_UP {
		fixture_var = 1;
		set_up_finished = true;
	}
};

COPPER_FIXTURE_TEST(fixture_test, the_fixture)
{
	COPPER_ASSERT(equal(fixture_var, 1));
	COPPER_ASSERT(set_up_finished);
}

// Tests of implementation details

COPPER_TEST(assertion_result_pass)
{
	using Copper::AssertionResult;
	AssertionResult ar = AssertionResult::pass();
	
	COPPER_ASSERT(ar.passed);
	COPPER_ASSERT(equal("", ar.message));
}

COPPER_TEST(assertion_result_failure)
{
	using Copper::AssertionResult;
	AssertionResult ar = AssertionResult::fail("Error goes here");
	
	COPPER_ASSERT(!ar.passed);
	COPPER_ASSERT(equal("Error goes here", ar.message));
}

COPPER_TEST(failure)
{
	Copper::Failure f("text", "message", "filename", 12345);
	
	COPPER_ASSERT(equal(f.Text, "text"));
	COPPER_ASSERT(equal(f.Message, "message"));
	COPPER_ASSERT(equal(f.File, "filename"));
	COPPER_ASSERT(equal(f.Line, 12345u));
}

COPPER_TEST(reverse_passed_assertion)
{
	using Copper::AssertionResult;
	AssertionResult ar = AssertionResult::pass(),
	                reversed_ar = failed(ar);
	
	COPPER_ASSERT(!reversed_ar.passed);
	COPPER_ASSERT(equal("Negative assertion succeeded",
	              reversed_ar.message));
}

COPPER_TEST(reverse_failed_assertion)
{
	using Copper::AssertionResult;
	AssertionResult ar = AssertionResult::fail(""),
	                reversed_ar = failed(ar);
	
	COPPER_ASSERT(reversed_ar.passed);
}

}
