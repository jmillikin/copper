/* assertions.hpp -- Available assertions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_ASSERTIONS_HPP
#define COPPER_ASSERTIONS_HPP

#include <copper/AssertionResult.hpp>
#include <copper/repr.hpp>

/**
 * @brief Assert two values are equal.
 * 
 * @param first The first value.
 * @param second The second value, which should equal the first value.
 * 
 * @return whether the values are equal.
 */
template <class First, class Second>
Copper::AssertionResult equal
	( const First &first
	, const Second &second
	)
{
	using namespace Copper;
	
	if (first == second)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(first, "!=", second));
}

/**
 * @brief Overloaded equal ()
 * @overload
 */
Copper::AssertionResult equal
	( const char *first
	, const char *second
	);

/**
 * @brief Overloaded equal ()
 * @overload
 */
Copper::AssertionResult equal
	( const char *first
	, char second[]
	);

/**
 * @brief Overloaded equal ()
 * @overload
 */
Copper::AssertionResult equal
	( char first[]
	, const char *second
	);

/**
 * @brief Overloaded equal ()
 * @overload
 */
Copper::AssertionResult equal
	( char first[]
	, char second[]
	);

/**
 * @brief Overloaded for performance
 * @overload
 */
Copper::AssertionResult equal
	( const char *first
	, const Copper::String &second
	);

/**
 * @brief Overloaded for performance
 * @overload
 */
Copper::AssertionResult equal
	( char first[]
	, const Copper::String &second
	);

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
Copper::AssertionResult equal_within
	( const Value &expected
	, const Value &actual
	, const Value &delta
	)
{
	using namespace Copper;
	
	if ((expected - delta < actual) && (expected + delta > actual))
	{ return AssertionResult::pass(); }
	
	String message = String::Build
		( repr(actual).CStr ()
		, " is not within "
		, repr(delta).CStr()
		, " of "
		, repr(expected).CStr()
		, NULL
		);
	return AssertionResult::fail(message);
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
Copper::AssertionResult unequal
	( const First &first
	, const Second &second
	)
{
	using namespace Copper;
	
	if (first != second)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(first, "==", second));
}

/**
 * @brief Overloaded unequal ()
 * @overload
 */
Copper::AssertionResult unequal
	( const char *first
	, const char *second
	);

/**
 * @brief Overloaded unequal ()
 * @overload
 */
Copper::AssertionResult unequal
	( const char *first
	, char second[]
	);

/**
 * @brief Overloaded unequal ()
 * @overload
 */
Copper::AssertionResult unequal
	( char first[]
	, const char *second
	);

/**
 * @brief Overloaded unequal ()
 * @overload
 */
Copper::AssertionResult unequal
	( char first[]
	, char second[]
	);

Copper::AssertionResult failed(const bool result);

Copper::AssertionResult failed(const Copper::AssertionResult &result);

/**
 * @brief Assert some pointer is NULL.
 * 
 * @param value The pointer to check for NULL-ness.
 * 
 * @return whether value == NULL.
 */
template <class Value>
Copper::AssertionResult is_null(const Value *value)
{
	using namespace Copper;
	
	if (value == NULL)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, "!= NULL"));
}

/**
 * @brief Assert some pointer is not NULL.
 * 
 * @param value The pointer to check for NULL-ness.
 * 
 * @return whether value != NULL.
 */
template <class Value>
Copper::AssertionResult not_null(const Value *value)
{
	using namespace Copper;
	
	if (value != NULL)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, "== NULL"));
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
Copper::AssertionResult greater_than
	( const Value &value
	, const Value &limit
	)
{
	using namespace Copper;
	
	if (value > limit)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, "<=", limit));
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
Copper::AssertionResult greater_than_or_equal
	( const Value &value
	, const Value &limit
	)
{
	using namespace Copper;
	
	if (value >= limit)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, "<", limit));
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
Copper::AssertionResult less_than
	( const Value &value
	, const Value &limit
	)
{
	using namespace Copper;
	
	if (value < limit)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, ">=", limit));
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
Copper::AssertionResult less_than_or_equal
	( const Value &value
	, const Value &limit
	)
{
	using namespace Copper;
	
	if (value <= limit)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, ">", limit));
}

#endif
