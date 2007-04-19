/* assertions.cpp -- Available assertions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "assertions.hpp"
#include "util/string.hpp"

Copper::AssertionResult
check_equal_strings (const char *expected, const char *actual) throw ()
{
	Copper::AssertionResult result;

	// Both of the values are NULL
	// assert (null ()) should be used instead
	if (!expected && !actual)
		result.pass ();

	else
		// One of the values is NULL
		result.fail (Copper::error_format (expected, "!=", actual));

	return result;
}

Copper::AssertionResult
check_unequal_strings (const char *bad, const char *actual) throw ()
{
	Copper::AssertionResult result;

	// Both of the values are NULL
	// assert (not_null ()) should be used instead
	if (!bad && !actual)
		result.fail (Copper::error_format (bad, "==", actual));

	else
		// Only one the values is NULL
		result.pass ();

	return result;
}

// Overloads for equal ()

Copper::AssertionResult
equal (const char *expected, const char *actual) throw ()
{
	if (!expected || !actual)
		return check_equal_strings (expected, actual);

	Copper::String s_expected (expected), s_actual (actual);
	return equal (s_expected, s_actual);
}

Copper::AssertionResult
equal (const char *expected, char actual[]) throw ()
{
	if (!expected || !actual)
		return check_equal_strings (expected, actual);

	Copper::String s_expected (expected), s_actual (actual);
	return equal (s_expected, s_actual);
}

Copper::AssertionResult
equal (char expected[], const char *actual) throw ()
{
	if (!expected || !actual)
		return check_equal_strings (expected, actual);

	Copper::String s_expected (expected), s_actual (actual);
	return equal (s_expected, s_actual);
}

Copper::AssertionResult
equal (char expected[], char actual[]) throw ()
{
	if (!expected || !actual)
		return check_equal_strings (expected, actual);

	Copper::String s_expected (expected), s_actual (actual);
	return equal (s_expected, s_actual);
}

// Overloads for unequal ()

Copper::AssertionResult
unequal (const char *bad, const char *actual) throw ()
{
	if (!bad || !actual)
		return check_unequal_strings (bad, actual);

	Copper::String s_actual (actual), s_bad (bad);
	return unequal (s_bad, s_actual);
}

Copper::AssertionResult
unequal (const char *bad, char actual[]) throw ()
{
	if (!bad || !actual)
		return check_unequal_strings (bad, actual);

	Copper::String s_actual (actual), s_bad (bad);
	return unequal (s_bad, s_actual);
}

Copper::AssertionResult
unequal (char bad[], const char *actual) throw ()
{
	if (!bad || !actual)
		return check_unequal_strings (bad, actual);

	Copper::String s_actual (actual), s_bad (bad);
	return unequal (s_bad, s_actual);
}

Copper::AssertionResult
unequal (char bad[], char actual[]) throw ()
{
	if (!bad || !actual)
		return check_unequal_strings (bad, actual);

	Copper::String s_actual (actual), s_bad (bad);
	return unequal (s_bad, s_actual);
}
