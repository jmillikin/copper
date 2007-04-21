/* assertion_result.cpp -- The result of a single assertion
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstring>
#include <cstdlib>

#include "assertion_result.hpp"

namespace Copper
{
	static
	String
	make_failure_message (bool passed) throw ()
	{
		if (!passed)
			return String::from_static ("Boolean assertion failed");
		else
			return String::from_static ("No Error");
	}


	/**
	 * @brief Implementation details of AssertionResult
	 */
	class AssertionResultPrivate
	{
	public:
		/**
		 * @brief Initialize with default values.
		 */
		AssertionResultPrivate () throw ():
	                                finished (false),
	                                passed (false),
	                                failure_message (String::from_static ("Unitialized AssertionResult"))
		{
		}

		/**
		 * @brief Initialize with a boolean result.
		 * 
		 * @param result Whether the assertion passed.
		 */
		AssertionResultPrivate (bool result) throw ():
		                        finished (true),
		                        passed (result),
		                        failure_message (make_failure_message (result))
		{
		}

		/**
		 * @brief True if pass () or fail () has been called.
		 */
		bool finished;

		/**
		 * @brief Whether the assertion passed or failed.
		 */
		bool passed;

		/**
		 * @brief The failure message, if available.
		 * 
		 * If the Assertion failed, this will contain the failure
		 * message.
		 */
		String failure_message;
	};


	/** @class AssertionResult
	 * @brief Detailed information about an assertion.
	 * 
	 * Used for returning whether an assertion passed or not.
	 */

	/**
	 * @brief Initialize with default values.
	 * 
	 * This initializes an AssertionResult that has been marked as not
	 * yet completed.
	 */
	AssertionResult::AssertionResult () throw ():
	                                  priv (new AssertionResultPrivate)
	{
	}

	/**
	 * @brief Initialize with a boolean result.
	 * 
	 * @param result Whether the assertion passed.
	 */
	AssertionResult::AssertionResult (bool result) throw ():
	                                  priv (new AssertionResultPrivate (result))
	{
	}

	/**
	 * @brief Copy an existing assertion result.
	 * 
	 * @param other The AssertionResult to copy.
	 */
	AssertionResult::AssertionResult (const AssertionResult &other) throw ():
	                                  priv (new AssertionResultPrivate)
	{
		priv->finished = other.priv->finished;
		priv->passed = other.priv->passed;
		priv->failure_message = other.priv->failure_message;
	}

	/**
	 * @brief Deallocate used memory.
	 */
	AssertionResult::~AssertionResult () throw ()
	{
		delete priv;
	}

	/** 
	 * @brief Mark that the assertion has passed.
	 * 
	 * If this function is called after this result has been marked as
	 * finished, nothing will happen.
	 */
	void
	AssertionResult::pass () throw ()
	{
		if (!priv->finished)
		{
			priv->passed = true;
			priv->finished = true;
			priv->failure_message = String::from_static ("No Error");
		}
	}

	/**
	 * @brief Mark that the Assertion has failed.
	 * 
	 * If this function is called after this result has been marked as
	 * finished, nothing will happen.
	 * 
	 * @param message The failure message.
	 * 
	 * @return The AssertionResult, for use in constructing failed
	 *         assertions with a single expression.
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

	/**
	 * @brief Get whether the assertion has passed or failed.
	 * 
	 * @return whether the assertion has passed or failed.
	 */
	bool
	AssertionResult::passed () const throw ()
	{
		return priv->finished && priv->passed;
	}

	/**
	 * @brief Get the failure message
	 * 
	 * If the result has not been set, or passed, an appropriate string
	 * will be returned instead of a failure message.
	 * 
	 * @return the failure message, if one exists.
	 */
	const String &
	AssertionResult::failure_message () const throw ()
	{
		return priv->failure_message;
	}

	/**
	 * @brief Automatic boolean conversion
	 * 
	 * @return whether the assertion has passed or failed.
	 */
	AssertionResult::operator bool () const throw ()
	{
		return passed ();
	}
}
