/* assertions.hpp -- Available assertions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_ASSERTIONS_HPP
#define COPPER_ASSERTIONS_HPP

#include <copper/AssertionResult.hpp>
#include <copper/FailureFormat.hpp>
#include <copper/compat.hpp>
#include <copper/FuncAttrs.hpp>

/**
 * @brief Assert two values are equal.
 * 
 * @param first The first value.
 * @param second The second value, which should equal the first value.
 * 
 * @return whether the values are equal.
 */
template <class First, class Second>
Copper::AssertionResult
equal (const First &first, const Second &second)
{
	using namespace Copper;

	if (first == second)
		return AssertionResult::pass ();

	else
	{
		String message (failure_format (first, "!=", second));
		return AssertionResult::fail (message);
	}
}

/**
 * @brief Overloaded equal ()
 * @overload
 */
COPPER_FUNCATTR_EXPORT
Copper::AssertionResult
equal (const char *first, const char *second);

/**
 * @brief Overloaded equal ()
 * @overload
 */
COPPER_FUNCATTR_EXPORT
Copper::AssertionResult
equal (const char *first, char second[]);

/**
 * @brief Overloaded equal ()
 * @overload
 */
COPPER_FUNCATTR_EXPORT
Copper::AssertionResult
equal (char first[], const char *second);

/**
 * @brief Overloaded equal ()
 * @overload
 */
COPPER_FUNCATTR_EXPORT
Copper::AssertionResult
equal (char first[], char second[]);

/**
 * @brief Overloaded for performance
 * @overload
 */
COPPER_FUNCATTR_EXPORT
Copper::AssertionResult
equal (const char *first, const Copper::String &second);

/**
 * @brief Overloaded for performance
 * @overload
 */
COPPER_FUNCATTR_EXPORT
Copper::AssertionResult
equal (char first[], const Copper::String &second);

/**
 * @brief Assert two values are nearly equal, within a certain delta.
 * 
 * @param expected The expected value of this assertion.
 * @param actual The value which should be tested against the expected value.
 * @param delta The allowable difference between the expected and actual
 *              values.
 * 
 * @return whether the values are nearly equal.
 */
template <class Value>
Copper::AssertionResult
equal_within (const Value &expected,
              const Value &actual,
              const Value &delta)
{
	using namespace Copper;

	if ((actual < expected - delta) || (actual > expected + delta))
	{
		String message (String::Build ("'",
		                               format (actual).CStr (),
		                               "'",
		                               " is not within '",
		                               format (delta).CStr (),
		                               "' of '",
		                               format (expected).CStr (),
		                               "'", NULL));
		return AssertionResult::fail (message);
	}

	else
		return AssertionResult::pass ();
}

/**
 * @brief Assert two values are not equal.
 * 
 * @param first The first value.
 * @param second The second value, which should not equal the first value.
 * 
 * @return whether the two values are unequal.
 */
template <class First, class Second>
Copper::AssertionResult
unequal (const First &first, const Second &second)
{
	using namespace Copper;

	if (first == second)
	{
		String message (failure_format (first, "==", second));
		return AssertionResult::fail (message);
	}

	else
		return AssertionResult::pass ();
}

/**
 * @brief Overloaded unequal ()
 * @overload
 */
COPPER_FUNCATTR_EXPORT
Copper::AssertionResult
unequal (const char *first, const char *second);

/**
 * @brief Overloaded unequal ()
 * @overload
 */
COPPER_FUNCATTR_EXPORT
Copper::AssertionResult
unequal (const char *first, char second[]);

/**
 * @brief Overloaded unequal ()
 * @overload
 */
COPPER_FUNCATTR_EXPORT
Copper::AssertionResult
unequal (char first[], const char *second);

/**
 * @brief Overloaded unequal ()
 * @overload
 */
COPPER_FUNCATTR_EXPORT
Copper::AssertionResult
unequal (char first[], char second[]);

/**
 * @brief Assert some pointer is NULL.
 * 
 * @param value The pointer to check for NULL-ness.
 * 
 * @return whether value == NULL.
 */
template <class Value>
Copper::AssertionResult
is_null (const Value *value)
{
	using namespace Copper;

	if (value != NULL)
	{
		String message (failure_format (value, "!= NULL"));
		return AssertionResult::fail (message);
	}

	else
		return AssertionResult::pass ();
}

/**
 * @brief Assert some pointer is not NULL.
 * 
 * @param value The pointer to check for NULL-ness.
 * 
 * @return whether value != NULL.
 */
template <class Value>
Copper::AssertionResult
not_null (const Value *value)
{
	using namespace Copper;

	if (value == NULL)
	{
		String message (failure_format (value, "== NULL"));
		return AssertionResult::fail (message);
	}

	else
		return AssertionResult::pass ();
}

/**
 * @brief Assert some value is greater than some limit.
 * 
 * @param value The value which should be tested against the limit.
 * @param limit The value the result must be above.
 * 
 * @return whether value > limit.
 */
template <class Value>
Copper::AssertionResult
greater_than (const Value &value, const Value &limit)
{
	using namespace Copper;

	if (value <= limit)
	{
		String message (failure_format (value, "<=", limit));
		return AssertionResult::fail (message);
	}

	else
		return AssertionResult::pass ();
}

/**
 * @brief Assert some value is greater than or equal to some limit.
 * 
 * @param value The value which should be tested against the limit.
 * @param limit The number the result must be above or equal to.
 * 
 * @return whether value >= limit.
 */
template <class Value>
Copper::AssertionResult
greater_than_or_equal (const Value &value, const Value &limit)
{
	using namespace Copper;

	if (value < limit)
	{
		String message (failure_format (value, "<", limit));
		return AssertionResult::fail (message);
	}

	else
		return AssertionResult::pass ();
}

/**
 * @brief Assert some value is less than some limit.
 * 
 * @param value The value which should be tested against the limit.
 * @param limit The number the result must be below.
 * 
 * @return whether value < limit.
 */
template <class Value>
Copper::AssertionResult
less_than (const Value &value, const Value &limit)
{
	using namespace Copper;

	if (value >= limit)
	{
		String message (failure_format (value, ">=", limit));
		return AssertionResult::fail (message);
	}

	else
		return AssertionResult::pass ();
}

/**
 * @brief Assert some value is less than or equal to some limit.
 * 
 * @param value The value which should be tested against the limit.
 * @param limit The number the result must be below or equal to.
 * 
 * @return whether value <= limit.
 */
template <class Value>
Copper::AssertionResult
less_than_or_equal (const Value &value, const Value &limit)
{
	using namespace Copper;

	if (value > limit)
	{
		String message (failure_format (value, ">", limit));
		return AssertionResult::fail (message);
	}

	else
		return AssertionResult::pass ();
}

#endif /* COPPER_ASSERTIONS_HPP */
