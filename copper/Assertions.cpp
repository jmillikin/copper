/* assertions.cpp -- Available assertions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/Assertions.hpp>
#include <copper/String.hpp>

using Copper::String;
using Copper::AssertionResult;

static
Copper::AssertionResult
check_equal_strings (const char *first, const char *second)
{
	// Both of the values are NULL
	// assert (null ()) should be used instead
	if (!first && !second)
		return AssertionResult::pass ();

	else
	{
		// One of the values is NULL
		String message (Copper::failure_format (first, "!=", second));
		return AssertionResult::fail (message);
	}
}

static
Copper::AssertionResult
check_unequal_strings (const char *first, const char *second)
{
	// Both of the values are NULL
	// assert (not_null ()) should be used instead
	if (!first && !second)
	{
		String message (Copper::failure_format (first, "==", second));
		return AssertionResult::fail (message);
	}

	else
		// Only one the values is NULL
		return AssertionResult::pass ();
}

// Overloads for equal ()

Copper::AssertionResult
_equal (const char *first, const char *second)
{
	if (!first || !second)
		return check_equal_strings (first, second);

	String s_first = String::NoCopy (first),
	       s_second = String::NoCopy (second);
	return equal (s_first, s_second);
}

Copper::AssertionResult
equal (const char *first, const char *second)
{
	return _equal (first, second);
}

Copper::AssertionResult
equal (const char *first, char second[])
{
	return _equal (first, second);
}

Copper::AssertionResult
equal (char first[], const char *second)
{
	return _equal (first, second);
}

Copper::AssertionResult
equal (char first[], char second[])
{
	return _equal (first, second);
}

Copper::AssertionResult
equal (const char *first, const String &second)
{
	return equal (String::NoCopy (first), second);
}

Copper::AssertionResult
equal (char first[], const String &second)
{
	return equal (String::NoCopy (first), second);
}

// Overloads for unequal ()

static
Copper::AssertionResult
_unequal (const char *first, const char *second)
{
	if (!first || !second)
		return check_unequal_strings (first, second);

	String s_first = String::NoCopy (first),
	       s_second = String::NoCopy (second);
	return unequal (s_first, s_second);
}

Copper::AssertionResult
unequal (const char *first, const char *second)
{
	return _unequal (first, second);
}

Copper::AssertionResult
unequal (const char *first, char second[])
{
	return _unequal (first, second);
}

Copper::AssertionResult
unequal (char first[], const char *second)
{
	return _unequal (first, second);
}

Copper::AssertionResult
unequal (char first[], char second[])
{
	return _unequal (first, second);
}

/**
 * Check that an assertion was false. If it was true, the current
 * failure handler will be executed.
 * 
 * @see failed ()
 * 
 * @param result The result of the assertion.
 */
AssertionResult
failed (const AssertionResult &result)
{
	if (result.passed)
	{ return AssertionResult::fail ("Negative assertion succeeded"); }
	
	return AssertionResult::pass ();
}

/**
 * Check that an assertion was false. If it was true, the current
 * failure handler will be executed.
 * 
 * @see failed ()
 * 
 * @param passed Whether the assertion passed.
 * @param text The code that this Assertion tests.
 */
AssertionResult
failed (const bool passed)
{
	if (passed)
	{ return AssertionResult::fail ("Negative assertion succeeded"); }
	
	return AssertionResult::pass ();
}

