/* self_tests.cpp -- Various self-tests of the framework
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>
#include <cstring>
#include <cstdlib>

#include <copper/OutputHandler.hpp>

// Various self-tests of the framework, to try and avoid bugs
COPPER_SUITE (self_tests)
{
	COPPER_FIXTURE (the_fixture)
	{
		int fixture_var = 0;
		bool set_up_finished = false;

		COPPER_SET_UP {
			fixture_var = 1;
			set_up_finished = true;
		}
	}

	COPPER_FIXTURE_TEST (fixture_test, the_fixture)
	{
		COPPER_ASSERT (equal (fixture_var, 1));
		COPPER_ASSERT (set_up_finished);
	}

	// Tests of implementation details

	COPPER_TEST (assertion_result_pass)
	{
		using Copper::AssertionResult;
		AssertionResult ar = AssertionResult::pass ();

		COPPER_ASSERT (ar.passed);
		COPPER_ASSERT (equal ("No Error", ar.failure_message));
	}

	COPPER_TEST (assertion_result_failure)
	{
		using Copper::AssertionResult;
		AssertionResult ar = AssertionResult::fail ("Error goes here");

		COPPER_ASSERT (!ar.passed);
		COPPER_ASSERT (equal ("Error goes here", ar.failure_message));
	}

	COPPER_TEST (failure)
	{
		Copper::Failure f ("text", "message", "filename", 12345);

		COPPER_ASSERT (equal (f.text, "text"));
		COPPER_ASSERT (equal (f.message, "message"));
		COPPER_ASSERT (equal (f.file, "filename"));
		COPPER_ASSERT (equal (f.line, 12345u));
	}

	COPPER_TEST (reverse_passed_assertion)
	{
		using Copper::AssertionResult;
		AssertionResult ar = AssertionResult::pass (),
		                reversed_ar = failed (ar);

		COPPER_ASSERT (!reversed_ar.passed);
		COPPER_ASSERT (equal ("Negative assertion succeeded",
		               reversed_ar.failure_message));
	}

	COPPER_TEST (reverse_failed_assertion)
	{
		using Copper::AssertionResult;
		AssertionResult ar = AssertionResult::fail (""),
		                reversed_ar = failed (ar);

		COPPER_ASSERT (reversed_ar.passed);
	}

	int
	external_function ()
	{
		COPPER_ASSERT (true);
		COPPER_ASSERT (failed (false));
		return 0;
	}

	COPPER_TEST (external_function_COPPER_ASSERT)
	{
		COPPER_ASSERT (equal (0, external_function ()));
	}
}
