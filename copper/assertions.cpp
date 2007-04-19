/* assertions.cpp -- Available assertions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "assertions.hpp"
#include "util/string.hpp"

Copper::AssertionResult
check_equal_strings (const char *first, const char *second) throw ()
{
	Copper::AssertionResult result;

	// Both of the values are NULL
	// assert (null ()) should be used instead
	if (!first && !second)
		result.pass ();

	else
		// One of the values is NULL
		result.fail (Copper::error_format (first, "!=", second));

	return result;
}

Copper::AssertionResult
check_unequal_strings (const char *first, const char *second) throw ()
{
	Copper::AssertionResult result;

	// Both of the values are NULL
	// assert (not_null ()) should be used instead
	if (!first && !second)
		result.fail (Copper::error_format (first, "==", second));

	else
		// Only one the values is NULL
		result.pass ();

	return result;
}

// Overloads for equal ()

Copper::AssertionResult
equal (const char *first, const char *second) throw ()
{
	if (!first || !second)
		return check_equal_strings (first, second);

	Copper::String s_first (first), s_second (second);
	return equal (s_first, s_second);
}

Copper::AssertionResult
equal (const char *first, char second[]) throw ()
{
	if (!first || !second)
		return check_equal_strings (first, second);

	Copper::String s_first (first), s_second (second);
	return equal (s_first, s_second);
}

Copper::AssertionResult
equal (char first[], const char *second) throw ()
{
	if (!first || !second)
		return check_equal_strings (first, second);

	Copper::String s_first (first), s_second (second);
	return equal (s_first, s_second);
}

Copper::AssertionResult
equal (char first[], char second[]) throw ()
{
	if (!first || !second)
		return check_equal_strings (first, second);

	Copper::String s_first (first), s_second (second);
	return equal (s_first, s_second);
}

// Overloads for unequal ()

Copper::AssertionResult
unequal (const char *first, const char *second) throw ()
{
	if (!first || !second)
		return check_unequal_strings (first, second);

	Copper::String s_second (second), s_first (first);
	return unequal (s_first, s_second);
}

Copper::AssertionResult
unequal (const char *first, char second[]) throw ()
{
	if (!first || !second)
		return check_unequal_strings (first, second);

	Copper::String s_second (second), s_first (first);
	return unequal (s_first, s_second);
}

Copper::AssertionResult
unequal (char first[], const char *second) throw ()
{
	if (!first || !second)
		return check_unequal_strings (first, second);

	Copper::String s_second (second), s_first (first);
	return unequal (s_first, s_second);
}

Copper::AssertionResult
unequal (char first[], char second[]) throw ()
{
	if (!first || !second)
		return check_unequal_strings (first, second);

	Copper::String s_second (second), s_first (first);
	return unequal (s_first, s_second);
}
