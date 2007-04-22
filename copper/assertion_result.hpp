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
	class String;

	class COPPER_EXPORT AssertionResult
	{
	public:
		~AssertionResult () throw ();

		static
		AssertionResult
		pass () throw ();

		static
		AssertionResult
		fail (const String &message) throw ();

		const bool passed;

		const String failure_message;

		operator bool () const throw ();

	private:
		AssertionResult () throw ();

		AssertionResult (const String &message) throw ();

		const AssertionResult &
		operator= (const AssertionResult &other) throw ();
	};
}

#endif /* COPPER_ASSERTION_RESULT_HPP */
