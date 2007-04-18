/* suite.hpp -- Groups tests into logical groups
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_SUITE_HPP
#define COPPER_SUITE_HPP

#include <copper/export.hpp>
#include <copper/util/list.hpp>
#include <copper/util/string.hpp>

namespace Copper
{
	class Test;

	class COPPER_EXPORT Suite
	{
	public:
		Suite (const String &name, void (*&)(), void (*&)()) throw ();

		~Suite () throw ();

		void
		add_test (Test *test) throw ();

		List<Test>
		get_tests () const throw ();

		static
		List<Suite>
		all_suites () throw ();

		/** This suite's name */
		const String name;

	private:
		class SuitePrivate *priv;

		Suite &
		operator= (const Suite&) throw ();

		Suite (const Suite&) throw ();
	};
}

#endif /* COPPER_SUITE_HPP */
