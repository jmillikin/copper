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
	 * Used for returning whether an assertion passed or not.
	 */

	/** @var AssertionResult::m_finished
	 * True if pass () or fail () has been called.
	 */

	/** @var AssertionResult::m_passed
	 * Whether the Assertion has passed or failed.
	 */

	/** @var AssertionResult::m_failure_message
	 * If the Assertion failed, this will contain the failure message.
	 */

	/** Default constructor */
	AssertionResult::AssertionResult () throw ():
	                                  m_finished (false),
	                                  m_passed (false),
	                                  m_failure_message ("Unitialized AssertionResult")
	{
	}

	/** Construct from a boolean value */
	AssertionResult::AssertionResult (bool result) throw ():
	                                  m_finished (true),
	                                  m_passed (result)
	{
		if (!passed ())
			m_failure_message = "Boolean assertion failed";

		else
			m_failure_message = "No Error";
	}

	/** Copy constructor */
	AssertionResult::AssertionResult (const AssertionResult &other) throw ()
	{
		m_finished = other.m_finished;
		m_passed = other.m_passed;
		m_failure_message = other.m_failure_message;
	}

	/** Assignment operator */
	const AssertionResult &
	AssertionResult::operator= (const AssertionResult &other) throw ()
	{
		m_finished = other.m_finished;
		m_passed = other.m_passed;
		m_failure_message = other.m_failure_message;

		return *this;
	}

	/** Default destructor */
	AssertionResult::~AssertionResult () throw ()
	{
	}

	/** Mark that the Assertion has passed */
	void
	AssertionResult::pass () throw ()
	{
		if (!m_finished)
		{
			m_passed = true;
			m_finished = true;
			m_failure_message = "No Error";
		}
	}

	/**
	 * Mark that the Assertion has failed
	 * 
	 * @param message The failure message
	 * 
	 * @return The AssertionResult, for use in constructing failed
	 *         assertions with a single expression
	 */
	const AssertionResult &
	AssertionResult::fail (const String &message) throw ()
	{
		if (!m_finished)
		{
			m_passed = false;
			m_finished = true;
			m_failure_message = message;
		}

		return *this;
	}

	/** Get whether the Assertion has passed or failed */
	bool
	AssertionResult::passed () const throw ()
	{
		return m_finished && m_passed;
	}

	/** If the Assertion failed, get the failure message */
	const String &
	AssertionResult::failure_message () const throw ()
	{
		return m_failure_message;
	}

	/**
	 * Allow automatic conversions to boolean, for operations
	 * such as AND-ing.
	 */
	AssertionResult::operator bool () const throw ()
	{
		return passed ();
	}
}
