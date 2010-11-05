/* assertions.cpp -- Available assertions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/Assertions.hpp>
#include <copper/String.hpp>

using Copper::String;
using Copper::AssertionResult;
using Copper::repr_expr;

// Overloads for equal ()

static AssertionResult cstr_equal(const char *first, const char *second)
{
	if (first == second)
	{ return AssertionResult::pass (); }
	
	if (first == NULL || second == NULL)
	{ return AssertionResult::fail(repr_expr(first, "!=", second)); }
	
	return equal
		( String::NoCopy(first)
		, String::NoCopy(second)
		);
}

AssertionResult equal(const char *first, const char *second)
{ return cstr_equal(first, second); }

AssertionResult equal(const char *first, char second[])
{ return cstr_equal(first, second); }

AssertionResult equal(char first[], const char *second)
{ return cstr_equal(first, second); }

AssertionResult equal(char first[], char second[])
{ return cstr_equal(first, second); }

AssertionResult equal(const char *first, const String &second)
{
	if (first == NULL)
	{ return AssertionResult::fail(repr_expr(first, "!=", second)); }
	
	return equal (String::NoCopy (first), second);
}

AssertionResult equal(char first[], const String &second)
{ return equal(String::NoCopy(first), second); }

// Overloads for unequal ()

static AssertionResult cstr_unequal(const char *first, const char *second)
{
	if (first == second)
	{ return AssertionResult::fail(repr_expr(first, "==", second)); }
	
	if (first == NULL || second == NULL)
	{ return AssertionResult::pass (); }
	
	return unequal
		( String::NoCopy(first)
		, String::NoCopy(second)
		);
}

AssertionResult unequal(const char *first, const char *second)
{ return cstr_unequal(first, second); }

AssertionResult unequal(const char *first, char second[])
{ return cstr_unequal(first, second); }

AssertionResult unequal(char first[], const char *second)
{ return cstr_unequal(first, second); }

AssertionResult unequal(char first[], char second[])
{ return cstr_unequal(first, second); }

/**
 * Check that an assertion was false. If it was true, the current
 * failure handler will be executed.
 * 
 * @see failed ()
 * 
 * @param result The result of the assertion.
 */
AssertionResult failed(const AssertionResult &result)
{ return failed(result.passed); }

/**
 * Check that an assertion was false. If it was true, the current
 * failure handler will be executed.
 * 
 * @see failed ()
 * 
 * @param passed Whether the assertion passed.
 * @param text The code that this Assertion tests.
 */
AssertionResult failed(const bool passed)
{
	if (passed)
	{ return AssertionResult::fail("Negative assertion succeeded"); }
	
	return AssertionResult::pass ();
}

