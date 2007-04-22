/* assertion_result.cpp -- The result of a single assertion
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstring>
#include <cstdlib>

#include "assertion_result.hpp"

namespace Copper
{
	/** @class AssertionResult
	 * @brief Detailed information about an assertion.
	 * 
	 * Used for returning whether an assertion passed or not.
	 */

	/** @var AssertionResult::passed
	 * @brief Whether the assertion passed.
	 */

	/** @var AssertionResult::failure_message
	 * @brief If the assertion failed, this will contain the failure
	 *        message.
	 */

	/**
	 * @brief Initialize a result for an assertion that passed.
	 */
	AssertionResult::AssertionResult () throw ():
	                                  passed (true),
	                                  failure_message (String::from_static ("No Error"))
	{
	}

	/**
	 * @brief Initialize a result for an assertion that failed.
	 * 
	 * @param message The failure message.
	 */
	AssertionResult::AssertionResult (const String &message) throw ():
	                                  passed (false),
	                                  failure_message (message)
	{
	}

	/**
	 * @brief Deallocate used memory.
	 */
	AssertionResult::~AssertionResult () throw ()
	{
	}

	/** 
	 * @brief Create a result that marks an assertion as passed.
	 * 
	 * @return a result marked as passed.
	 */
	AssertionResult
	AssertionResult::pass () throw ()
	{
		return AssertionResult ();
	}

	/**
	 * @brief Mark that the Assertion has failed.
	 * 
	 * If this function is called after this result has been marked as
	 * finished, nothing will happen.
	 * 
	 * @param message The failure message.
	 * 
	 * @return a result marked as passed, with the given message.
	 */
	AssertionResult
	AssertionResult::fail (const String &message) throw ()
	{
		return AssertionResult (message);
	}

	/**
	 * @brief Automatic boolean conversion
	 * 
	 * @return whether the assertion has passed or failed.
	 */
	AssertionResult::operator bool () const throw ()
	{
		return passed;
	}
}
