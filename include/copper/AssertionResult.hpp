/* assertion_result.hpp -- The result of a single assertion
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_ASSERTION_RESULT_HPP
#define COPPER_ASSERTION_RESULT_HPP

#include <copper/String.hpp>
#include <copper/FuncAttrs.hpp>

namespace Copper
{
	class String;

	class COPPER_FUNCATTR_EXPORT AssertionResult
	{
	public:
		~AssertionResult ();

		static
		AssertionResult
		pass ();

		static
		AssertionResult
		fail (const String &message);

		const bool passed;

		const String failure_message;

		operator bool () const;

	private:
		AssertionResult ();

		AssertionResult (const String &message);

		const AssertionResult &
		operator= (const AssertionResult &other);
	};
}

#endif /* COPPER_ASSERTION_RESULT_HPP */
