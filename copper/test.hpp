/* test.hpp -- Runs a single unit test
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_HPP
#define COPPER_TEST_HPP

#include <copper/suite.hpp>
#include <copper/util/list.hpp>
#include <copper/util/string.hpp>
#include <copper/export.hpp>

namespace Copper
{
	class EXPORT Test {
	public:
		Test (const String &name,
		      Suite *suite,
		      const String &file_name) throw ();

		virtual
		~Test ();

		static
		List<Test>
		all ();

		/** Run the test */
		virtual
		void
		run () = 0;

		virtual
		void
		set_up ();

		virtual
		void
		tear_down ();

		const String name;

		const Suite *suite;

		const String file_name;

	private:
		Test &
		operator= (const Test&) throw ();

		Test (const Test&) throw ();
	};
}

#endif /* COPPER_TEST_HPP */
