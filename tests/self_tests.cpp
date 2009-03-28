/* self_tests.cpp -- Various self-tests of the framework
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>
#include <cstring>
#include <cstdlib>

#include <copper/OutputHandler.hpp>

// Various self-tests of the framework, to try and avoid bugs
SUITE (self_tests)
{
	FIXTURE (the_fixture)
	{
		int fixture_var = 0;
		bool set_up_finished = false;

		SET_UP {
			fixture_var = 1;
			set_up_finished = true;
		}
	}

	FIXTURE_TEST (fixture_test, the_fixture)
	{
		ASSERT (equal (fixture_var, 1));
		ASSERT (set_up_finished);
	}

	// Tests of implementation details

	TEST (assertion_result_pass)
	{
		using Copper::AssertionResult;
		AssertionResult ar = AssertionResult::pass ();

		ASSERT (ar.passed);
		ASSERT (equal ("No Error", ar.failure_message));
	}

	TEST (assertion_result_failure)
	{
		using Copper::AssertionResult;
		AssertionResult ar = AssertionResult::fail ("Error goes here");

		ASSERT (!ar.passed);
		ASSERT (equal ("Error goes here", ar.failure_message));
	}

	TEST (failure)
	{
		Copper::Failure f ("text", "message", "filename", 12345);

		ASSERT (equal (f.text, "text"));
		ASSERT (equal (f.message, "message"));
		ASSERT (equal (f.file, "filename"));
		ASSERT (equal (f.line, 12345u));
	}

	TEST (reverse_passed_assertion)
	{
		using Copper::AssertionResult;
		AssertionResult ar = AssertionResult::pass (),
		                reversed_ar = failed (ar);

		ASSERT (!reversed_ar.passed);
		ASSERT (equal ("Unexpected success of assertion 'ar'",
		               reversed_ar.failure_message));
	}

	TEST (reverse_failed_assertion)
	{
		using Copper::AssertionResult;
		AssertionResult ar = AssertionResult::fail (""),
		                reversed_ar = failed (ar);

		ASSERT (reversed_ar.passed);
	}

	int
	external_function ()
	{
		ASSERT (true);
		ASSERT (failed (false));
		return 0;
	}

	TEST (external_function_ASSERT)
	{
		ASSERT (equal (0, external_function ()));
	}
}
