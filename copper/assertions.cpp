/* assertions.cpp -- Available assertions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "assertions.hpp"
#include "util/string.hpp"

using Copper::String;
using Copper::AssertionResult;

static
Copper::AssertionResult
check_equal_strings (const char *first, const char *second) throw ()
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
check_unequal_strings (const char *first, const char *second) throw ()
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
_equal (const char *first, const char *second) throw ()
{
	if (!first || !second)
		return check_equal_strings (first, second);

	String s_first = String::from_static (first),
	       s_second = String::from_static (second);
	return equal (s_first, s_second);
}

Copper::AssertionResult
equal (const char *first, const char *second) throw ()
{
	return _equal (first, second);
}

Copper::AssertionResult
equal (const char *first, char second[]) throw ()
{
	return _equal (first, second);
}

Copper::AssertionResult
equal (char first[], const char *second) throw ()
{
	return _equal (first, second);
}

Copper::AssertionResult
equal (char first[], char second[]) throw ()
{
	return _equal (first, second);
}

Copper::AssertionResult
equal (const char *first, const String &second) throw ()
{
	return equal (String::from_static (first), second);
}

Copper::AssertionResult
equal (char first[], const String &second) throw ()
{
	return equal (String::from_static (first), second);
}

// Overloads for unequal ()

static
Copper::AssertionResult
_unequal (const char *first, const char *second) throw ()
{
	if (!first || !second)
		return check_unequal_strings (first, second);

	String s_first = String::from_static (first),
	       s_second = String::from_static (second);
	return unequal (s_first, s_second);
}

Copper::AssertionResult
unequal (const char *first, const char *second) throw ()
{
	return _unequal (first, second);
}

Copper::AssertionResult
unequal (const char *first, char second[]) throw ()
{
	return _unequal (first, second);
}

Copper::AssertionResult
unequal (char first[], const char *second) throw ()
{
	return _unequal (first, second);
}

Copper::AssertionResult
unequal (char first[], char second[]) throw ()
{
	return _unequal (first, second);
}
