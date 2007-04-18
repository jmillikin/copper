/* test.cpp -- Runs a single unit test
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "suite.hpp"
#include "test.hpp"

namespace Copper
{
	/** @class Test
	 * Does nothing interesting by itself, but is subclassed to provide
	 * runnable test classes.
	 */

	/** @var Test::name
	 * The name of this test.
	 */

	/** @var Test::suite
	 * The suite this test is part of.
	 */

	/** @var Test::file_name
	 * The file this test's implementation is in.
	 */

	/** @var Test::line
	 * The line this test was defined on.
	 */

	/**
	 * Constructs a new test.
	 * 
	 * @param name The name of this test.
	 * @param suite The suite this test is part of.
	 * @param file_name The file this test's implementation is in.
	 * @param line The line this test was defined on.
	 */
	Test::Test (const String &name,
	            Suite *suite,
	            const String &file_name,
	            const unsigned int line) throw ():

	            name (name),
	            suite (suite),
	            file_name (file_name),
	            line (line)
	{
		if (suite)
			suite->add_test (this);
	}

	/** Default destructor */
	Test::~Test ()
	{
	}

	/** Get a list of all tests */
	List<Test>
	Test::all ()
	{
		List<Test> all_tests;

		List<Suite> suites = Suite::all_suites ();
		const ListNode<Suite>* suite = suites.root ();

		while (suite)
		{
			List<Test> tests = suite->value->get_tests ();
			const ListNode<Test> *test = tests.root ();

			while (test)
			{
				all_tests.append (test->value);
				test = test->next;
			}

			suite = suite->next;
		}

		return all_tests;
	}

	/** Default, does nothing */
	void
	Test::set_up ()
	{
	}

	/** Default, does nothing */
	void
	Test::tear_down ()
	{
	}

}
