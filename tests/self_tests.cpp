/* self_tests.cpp - Various self-tests of the framework
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>
#include <cstring>
#include <cstdlib>

#include <copper/output_handler.hpp>

// Various self-tests of the framework, to try and avoid bugs
TEST_SUITE (self_tests)
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

	TEST (assertion_result_fresh)
	{
		Copper::AssertionResult ar;
		ASSERT (!ar.passed ());
		ASSERT (equal ("Unitialized AssertionResult",
		               ar.failure_message ()));
	}

	TEST (assertion_result_pass)
	{
		Copper::AssertionResult ar;
		ar.pass ();

		ASSERT (ar.passed ());
		ASSERT (equal ("No Error", ar.failure_message ()));

		ar.fail ("Bad fail");
		ASSERT (ar.passed ());
		ASSERT (equal ("No Error", ar.failure_message ()));
	}

	TEST (assertion_result_failure)
	{
		Copper::AssertionResult ar;
		ar.fail ("Error goes here");

		ASSERT (!ar.passed ());
		ASSERT (equal ("Error goes here", ar.failure_message ()));

		ar.pass ();
		ASSERT (!ar.passed ());
		ASSERT (equal ("Error goes here", ar.failure_message ()));
	}

	TEST (boolean_assertion_pass)
	{
		Copper::AssertionResult ar (true);
		ASSERT (ar.passed ());
	}

	TEST (boolean_assertion_failure)
	{
		Copper::AssertionResult ar (false);
		ASSERT (!ar.passed ());
		ASSERT (equal ("Boolean assertion failed",
		               ar.failure_message ()));
	}

	TEST (assertion_pass)
	{
		Copper::AssertionResult ar;
		ar.pass ();
		Copper::Assertion a (ar, "Assertion text", 12345);

		ASSERT (a.passed ());
		ASSERT (equal ("Assertion text", a.text ()));
		ASSERT (equal (12345u, a.line ()));
	}

	TEST (assertion_failure)
	{
		Copper::AssertionResult ar;
		ar.fail ("Error goes here");
		Copper::Assertion a (ar, "Assertion text", 12345);

		ASSERT (!a.passed ());
		ASSERT (equal ("Assertion text", a.text ()));
		ASSERT (equal (12345u, a.line ()));
		ASSERT (equal ("Error goes here", a.failure_message ()));
	}

	TEST (assertion_failure_custom_message)
	{
		Copper::AssertionResult ar;
		ar.fail ("Error goes here");
		Copper::Assertion a (ar, "Assertion text", "Custom error",
		                     12345);

		ASSERT (!a.passed ());
		ASSERT (equal ("Assertion text", a.text ()));
		ASSERT (equal (12345u, a.line ()));
		ASSERT (equal ("Custom error", a.failure_message ()));
	}

	TEST (reverse_passed_assertion)
	{
		Copper::AssertionResult ar;
		ar.pass ();
		Copper::AssertionResult reversed_ar = failed (ar);

		ASSERT (!reversed_ar.passed ());
		ASSERT (equal ("Unexpected success of assertion 'ar'",
		               reversed_ar.failure_message ()));
	}

	TEST (reverse_failed_assertion)
	{
		Copper::AssertionResult ar;
		ar.fail ("");
		Copper::AssertionResult reversed_ar = failed (ar);

		ASSERT (reversed_ar.passed ());
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
