/* test.hpp -- Runs a single unit test
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_HPP
#define COPPER_TEST_HPP

#include <copper/util/list.hpp>
#include <copper/util/string.hpp>
#include <copper/export.hpp>

namespace Copper
{
	class COPPER_EXPORT Test
	{
	public:
		Test (const char name[],
		      const char suite[],
		      const char file_name[],
		      const unsigned int line) throw ();

		virtual
		~Test ();

		static
		const List<Test> &
		all ();

		static
		Test *
		find (const String &suite_name,
		      const String &test_name) throw ();

		static
		List<Test>
		in_suite (const String &suite_name) throw ();

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

		const String suite;

		const String file_name;

		const unsigned int line;

	private:
		Test &
		operator= (const Test&) throw ();

		Test (const Test&) throw ();
	};
}

#endif /* COPPER_TEST_HPP */
