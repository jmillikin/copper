/* assertions.cpp - Available assertions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/assertions.hpp>
#include <copper/util/string.hpp>
#include "export.hpp"

// Used for when the user passes NULL to a string comparison assertion
Copper::String
check_NULL (const char *str) throw ()
{
	using Copper::String;

	if (str)
		return String ("'") + String (str) + String ("'");

	else
		return String ("NULL");
}

Copper::AssertionResult
check_equal_strings (const char *expected, const char *actual) throw ()
{
	using Copper::String;

	Copper::AssertionResult result;

	// Both of the values are NULL
	// assert (null ()) should be used instead
	if (!expected && !actual)
	{
		result.pass ();
	}

	else
	{
		// One of the values is NULL
		result.fail (String ("Unequal values: expected ") +
		             check_NULL (expected) + String (", got ") +
		             check_NULL (actual));
	}

	return result;
}

Copper::AssertionResult
check_unequal_strings (const char *bad, const char *actual) throw ()
{

	using Copper::String;

	Copper::AssertionResult result;

	// Both of the values are NULL
	// assert (not_null ()) should be used instead
	if (!bad && !actual)
	{
		result.fail (check_NULL (actual) + String (" is equal to ") +
		             check_NULL (bad));
	}

	else
	{
		// Only one the values is NULL
		result.pass ();
	}

	return result;
}

// Overloads for equal ()

EXPORT
Copper::AssertionResult
equal (const char *expected, const char *actual) throw ()
{
	if (!expected || !actual)
		return check_equal_strings (expected, actual);

	Copper::String s_expected (expected), s_actual (actual);
	return equal (s_expected, s_actual);
}

EXPORT
Copper::AssertionResult
equal (const char *expected, char actual[]) throw ()
{
	if (!expected || !actual)
		return check_equal_strings (expected, actual);

	Copper::String s_expected (expected), s_actual (actual);
	return equal (s_expected, s_actual);
}

EXPORT
Copper::AssertionResult
equal (char expected[], const char *actual) throw ()
{
	if (!expected || !actual)
		return check_equal_strings (expected, actual);

	Copper::String s_expected (expected), s_actual (actual);
	return equal (s_expected, s_actual);
}

EXPORT
Copper::AssertionResult
equal (char expected[], char actual[]) throw ()
{
	if (!expected || !actual)
		return check_equal_strings (expected, actual);

	Copper::String s_expected (expected), s_actual (actual);
	return equal (s_expected, s_actual);
}

// Overloads for unequal ()

EXPORT
Copper::AssertionResult
unequal (const char *bad, const char *actual) throw ()
{
	if (!bad || !actual)
		return check_unequal_strings (bad, actual);

	Copper::String s_actual (actual), s_bad (bad);
	return unequal (s_bad, s_actual);
}

EXPORT
Copper::AssertionResult
unequal (const char *bad, char actual[]) throw ()
{
	if (!bad || !actual)
		return check_unequal_strings (bad, actual);

	Copper::String s_actual (actual), s_bad (bad);
	return unequal (s_bad, s_actual);
}

EXPORT
Copper::AssertionResult
unequal (char bad[], const char *actual) throw ()
{
	if (!bad || !actual)
		return check_unequal_strings (bad, actual);

	Copper::String s_actual (actual), s_bad (bad);
	return unequal (s_bad, s_actual);
}

EXPORT
Copper::AssertionResult
unequal (char bad[], char actual[]) throw ()
{
	if (!bad || !actual)
		return check_unequal_strings (bad, actual);

	Copper::String s_actual (actual), s_bad (bad);
	return unequal (s_bad, s_actual);
}
