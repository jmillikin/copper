/* test.cpp -- Runs a single unit test
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/Test.hpp>

namespace Copper
{
	List<Test> &
	all_tests ()
	{
		static List<Test> _tests;
		return _tests;
	}

	/** @class Test
	 * @brief Abstract base class for tests.
	 * 
	 * Does nothing interesting by itself, but is subclassed to provide
	 * runnable test classes.
	 */

	/** @var Test::name
	 * @brief The name of this test.
	 */

	/** @var Test::suite
	 * @brief The suite this test is part of.
	 */

	/** @var Test::file_name
	 * @brief The file this test's implementation is in.
	 */

	/** @var Test::line
	 * @brief The line this test was defined on.
	 */

	/**
	 * @brief Constructs a new test.
	 * 
	 * @param name The name of this test. This must be static data.
	 * @param suite The suite this test is part of. This must be
	 *              static data.
	 * @param file_name The file this test's implementation is in.
	 *                  This must be static data.
	 * @param line The line this test was defined on.
	 */
	Test::Test (const char name[],
	            const char suite[],
	            const char file_name[],
	            const unsigned int line):

	            name (String::FromStatic (name)),
	            suite (String::FromStatic (suite)),
	            file_name (String::FromStatic (file_name)),
	            line (line)
	{
		all_tests ().append (this);
	}

	/**
	 * @brief Default destructor
	 */
	Test::~Test ()
	{
	}

	/**
	 * @brief Get a list of all tests
	 * 
	 * @return a list of all tests.
	 */
	const List<Test> &
	Test::all ()
	{
		return all_tests ();
	}

	struct MatchInfo
	{
		const String *suite_name;
		const String *test_name;
	};

	static
	bool
	full_matcher (const Test *key, const void *data)
	{
		const MatchInfo *info = static_cast <const MatchInfo *> (data);
		return (key->name == *(info->test_name)) &&
		       (key->suite == *(info->suite_name));
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
	            const String &test_name)
	{
		const ListNode<Test> *node;
		MatchInfo info = { &suite_name, &test_name };
		node = all_tests ().find (full_matcher, &info);

		if (node)
			return node->value;

		return NULL;
	}

	static
	bool
	suite_matcher (const Test *key, const void *data)
	{
		const MatchInfo *info = static_cast <const MatchInfo *> (data);
		return (key->suite == *(info->suite_name));
	}

	/**
	 * @brief Find all tests in a suite.
	 * 
	 * @param suite_name The name of the suite to find tests in.
	 * 
	 * @return a list of tests in the suite.
	 */
	List<Test>
	Test::in_suite (const String &suite_name)
	{
		MatchInfo info = { &suite_name, NULL };
		return all_tests ().filter (suite_matcher, &info);
	}

	/**
	 * @brief Does nothing
	 */
	void
	Test::set_up ()
	{
	}

	/**
	 * @brief Does nothing
	 */
	void
	Test::tear_down ()
	{
	}
}
