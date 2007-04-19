/* assertions.hpp -- Available assertions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_ASSERTIONS_HPP
#define COPPER_ASSERTIONS_HPP

#include <copper/assertion_result.hpp>
#include <copper/compat.hpp>
#include <copper/export.hpp>
#include <copper/util/formatters.hpp>

/**
 * @brief Assert two values are equal.
 * 
 * @param expected The expected value of this assertion.
 * @param actual The value which should be tested against the expected value.
 * 
 * @return whether the values are equal.
 */
template <class Expected, class Actual>
Copper::AssertionResult
equal (const Expected &expected, const Actual &actual) throw ()
{
	Copper::AssertionResult result;
	if (expected == actual)
		result.pass ();

	else
	{
		Copper::String message;

		message = Copper::String ("Unequal values: expected '") + 
		                          Copper::format (expected) +
		                          "', got '" +
		                          Copper::format (actual) + "'";

		result.fail (message);
	}

	return result;
}

/**
 * @brief Overloaded equal ()
 * @overload
 */
COPPER_EXPORT
Copper::AssertionResult
equal (const char *expected, const char *actual) throw ();

/**
 * @brief Overloaded equal ()
 * @overload
 */
COPPER_EXPORT
Copper::AssertionResult
equal (const char *expected, char actual[]) throw ();

/**
 * @brief Overloaded equal ()
 * @overload
 */
COPPER_EXPORT
Copper::AssertionResult
equal (char expected[], const char *actual) throw ();

/**
 * @brief Overloaded equal ()
 * @overload
 */
COPPER_EXPORT
Copper::AssertionResult
equal (char expected[], char actual[]) throw ();

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
              const Value &delta) throw ()
{
	Copper::AssertionResult result;

	if ((actual < expected - delta) || (actual > expected + delta))
	{
		Copper::String message;
		message = Copper::String ("'") + Copper::format (actual) + "'"
		          " is not within '" + Copper::format (delta) +
		          "' of '" + Copper::format (expected) + "'";

		result.fail (message);
	}

	else
		result.pass ();

	return result;
}

/**
 * @brief Assert two values are not equal.
 * 
 * @param bad Something that actual should not be.
 * @param actual The value which should be tested against the expected value.
 * 
 * @return whether the two values are unequal.
 */
template <class Bad, class Actual>
Copper::AssertionResult
unequal (const Bad &bad, const Actual &actual) throw ()
{
	Copper::AssertionResult result;

	if (actual == bad)
	{
		Copper::String message;
		message = Copper::String ("'") + Copper::format (actual) + "'"
		          " is equal to '" + Copper::format (bad) + "'";

		result.fail (message);
	}

	else
		result.pass ();

	return result;
}

/**
 * @brief Overloaded unequal ()
 * @overload
 */
COPPER_EXPORT
Copper::AssertionResult
unequal (const char *bad, const char *actual) throw ();

/**
 * @brief Overloaded unequal ()
 * @overload
 */
COPPER_EXPORT
Copper::AssertionResult
unequal (const char *bad, char actual[]) throw ();

/**
 * @brief Overloaded unequal ()
 * @overload
 */
COPPER_EXPORT
Copper::AssertionResult
unequal (char bad[], const char *actual) throw ();

/**
 * @brief Overloaded unequal ()
 * @overload
 */
COPPER_EXPORT
Copper::AssertionResult
unequal (char bad[], char actual[]) throw ();

/**
 * @brief Assert some pointer is NULL.
 * 
 * @param value The pointer to check for NULL-ness.
 * 
 * @return whether value == NULL.
 */
template <class Value>
Copper::AssertionResult
is_null (const Value *value) throw ()
{
	Copper::AssertionResult result;

	if (value != 0)
		result.fail ("Expected value to be NULL");

	else
		result.pass ();

	return result;
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
not_null (const Value *value) throw ()
{
	Copper::AssertionResult result;

	if (value == 0)
		result.fail ("Expected value to be non-NULL");

	else
		result.pass ();

	return result;
}

/**
 * @brief Assert some value is greater than some limit.
 * 
 * @param actual The value which should be tested against the limit.
 * @param limit The value the result must be above.
 * 
 * @return whether value > limit.
 */
template <class Value>
Copper::AssertionResult
greater_than (const Value &actual, const Value &limit) throw ()
{
	Copper::AssertionResult result;

	if (actual <= limit)
	{
		Copper::String message;
		message = Copper::String ("'") + Copper::format (actual) + "'"
		          " is not greater than '" + Copper::format (limit) + "'";

		result.fail (message);
	}

	else
		result.pass ();

	return result;
}

/**
 * @brief Assert some value is greater than or equal to some limit.
 * 
 * @param actual The value which should be tested against the limit.
 * @param limit The number the result must be above or equal to.
 * 
 * @return whether value >= limit.
 */
template <class Value>
Copper::AssertionResult
greater_than_or_equal (const Value &actual, const Value &limit) throw ()
{
	Copper::AssertionResult result;

	if (actual < limit)
	{
		Copper::String message;
		message = Copper::String ("'") + Copper::format (actual) + "'"
		          " is less than '" + Copper::format (limit) + "'";

		result.fail (message);
	}

	else
		result.pass ();

	return result;
}

/**
 * @brief Assert some value is less than some limit.
 * 
 * @param actual The value which should be tested against the limit.
 * @param limit The number the result must be below.
 * 
 * @return whether value < limit.
 */
template <class Value>
Copper::AssertionResult
less_than (const Value &actual, const Value &limit) throw ()
{
	Copper::AssertionResult result;

	if (actual >= limit)
	{
		Copper::String message;
		message = Copper::String ("'") + Copper::format (actual) + "'"
		          " is not less than '" + Copper::format (limit) + "'";

		result.fail (message);
	}

	else
		result.pass ();

	return result;
}

/**
 * @brief Assert some value is less than or equal to some limit.
 * 
 * @param actual The value which should be tested against the limit.
 * @param limit The number the result must be below or equal to.
 * 
 * @return whether value <= limit.
 */
template <class Value>
Copper::AssertionResult
less_than_or_equal (const Value &actual, const Value &limit) throw ()
{
	Copper::AssertionResult result;

	if (actual > limit)
	{
		Copper::String message;
		message = Copper::String ("'") + Copper::format (actual) + "'"
		          " is greater than '" + Copper::format (limit) + "'";

		result.fail (message);
	}

	else
		result.pass ();

	return result;
}

#endif /* COPPER_ASSERTIONS_HPP */
