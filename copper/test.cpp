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
		const ListNode<Suite>* suite_node = suites.root ();

		while (suite_node)
		{
			all_tests.extend (suite_node->value->get_tests ());
			suite_node = suite_node->next;
		}

		return all_tests;
	}

	static
	bool
	matcher (const Test *key, const void *data)
	{
		return key->name == *static_cast<const String *> (data);
	}

	/**
	 * @brief Find a named test.
	 * 
	 * @param suite_name The name of the suite containing this test.
	 * @param test_name The name of the test.
	 * 
	 * @return The test with the given name, or NULL if no such
	 *         test exists.
	 */
	Test *
	Test::find (const String &suite_name,
	            const String &test_name) throw ()
	{
		// Find the suite
		const Suite *suite = Suite::find (suite_name);

		if (suite)
		{
			const ListNode<Test> *node;
			node = suite->get_tests ().find (matcher,
			                                 &test_name);

			if (node)
				return node->value;
		}

		return NULL;
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
