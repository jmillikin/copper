/* assertion_result.hpp -- The result of a single assertion
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_ASSERTION_RESULT_HPP
#define COPPER_ASSERTION_RESULT_HPP

#include <copper/compat.hpp>
#include <copper/export.hpp>
#include <copper/util/string.hpp>

namespace Copper
{
	class COPPER_EXPORT AssertionResult
	{
	public:
		AssertionResult () throw ();

		AssertionResult (bool result) throw ();

		AssertionResult (const AssertionResult &other) throw ();

		const AssertionResult &
		operator= (const AssertionResult &other) throw ();

		~AssertionResult () throw ();

		void
		pass () throw ();

		const AssertionResult &
		fail (const String &message) throw ();

		bool
		passed () const throw ();

		const String &
		failure_message () const throw ();

		operator bool () const throw ();

	protected:
		bool m_finished;

		bool m_passed;

		String m_failure_message;
	};
}

#endif /* COPPER_ASSERTION_RESULT_HPP */
