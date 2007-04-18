/* assertion_result.cpp -- The result of a single assertion
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstring>
#include <cstdlib>

#include "assertion_result.hpp"

namespace Copper
{
	class AssertionResultPrivate
	{
	public:
		AssertionResultPrivate () throw ():
	                                finished (false),
	                                passed (false),
	                                failure_message ("Unitialized AssertionResult")
		{
		}

		AssertionResultPrivate (bool result) throw ():
		                        finished (true),
		                        passed (result)
		{
		}

		bool finished;
		bool passed;
		String failure_message;
	};


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
	                                  priv (new AssertionResultPrivate)
	{
	}

	/** Construct from a boolean value */
	AssertionResult::AssertionResult (bool result) throw ():
	                                  priv (new AssertionResultPrivate (result))
	{
		if (!priv->passed)
			priv->failure_message = "Boolean assertion failed";

		else
			priv->failure_message = "No Error";
	}

	/** Copy constructor */
	AssertionResult::AssertionResult (const AssertionResult &other) throw ():
	                                  priv (new AssertionResultPrivate)
	{
		priv->finished = other.priv->finished;
		priv->passed = other.priv->passed;
		priv->failure_message = other.priv->failure_message;
	}

	/** Assignment operator */
	const AssertionResult &
	AssertionResult::operator= (const AssertionResult &other) throw ()
	{
		priv->finished = other.priv->finished;
		priv->passed = other.priv->passed;
		priv->failure_message = other.priv->failure_message;

		return *this;
	}

	/** Default destructor */
	AssertionResult::~AssertionResult () throw ()
	{
		delete priv;
	}

	/** Mark that the Assertion has passed */
	void
	AssertionResult::pass () throw ()
	{
		if (!priv->finished)
		{
			priv->passed = true;
			priv->finished = true;
			priv->failure_message = "No Error";
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
		if (!priv->finished)
		{
			priv->passed = false;
			priv->finished = true;
			priv->failure_message = message;
		}

		return *this;
	}

	/** Get whether the Assertion has passed or failed */
	bool
	AssertionResult::passed () const throw ()
	{
		return priv->finished && priv->passed;
	}

	/** If the Assertion failed, get the failure message */
	const String &
	AssertionResult::failure_message () const throw ()
	{
		return priv->failure_message;
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
