/* assertion_result.hpp -- The result of a single assertion
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_ASSERTION_RESULT_HPP
#define COPPER_ASSERTION_RESULT_HPP

#include <copper/util/string.hpp>
#include <copper/compat.hpp>

namespace Copper
{
	class AssertionResult
	{
	public:
		/** Default constructor */
		AssertionResult () throw ();

		/** Construct from a boolean value */
		AssertionResult (bool result) throw ();

		/** Copy constructor */
		AssertionResult (const AssertionResult &other) throw ();

		/** Assignment operator */
		const AssertionResult &
		operator= (const AssertionResult &other) throw ();

		/** Default destructor */
		~AssertionResult () throw ();

		/** Mark that the Assertion has passed */
		void
		pass () throw ();

		/**
		 * Mark that the Assertion has failed
		 * 
		 * @param message The failure message
		 * 
		 * @return The AssertionResult, for use in constructing failed
		 *         assertions with a single expression
		 */
		const AssertionResult &
		fail (const String &message) throw ();

		/** Get whether the Assertion has passed or failed */
		bool
		passed () const throw ();

		/** If the Assertion failed, get the failure message */
		const String &
		failure_message () const throw ();

		/**
		 * Allow automatic conversions to boolean, for operations
		 * such as AND-ing.
		 */
		operator bool () const throw ();

	protected:
		/** True if pass () or fail () has been called */
		bool m_finished;

		/** Whether the Assertion has passed or failed */
		bool m_passed;

		/**
		 * If the Assertion failed, this will contain the failure
		 * message
		 */
		String m_failure_message;
	};
}

#endif /* COPPER_ASSERTION_RESULT_HPP */
