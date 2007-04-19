/* suite.cpp -- Groups tests into logical groups
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "suite.hpp"

namespace Copper
{
	class SuitePrivate
	{
	public:
		/** All tests in this suite, in no particular order. */
		List<Test> tests;
	};

	/** @class Suite
	 */

	List<Suite>&
	suites () throw ()
	{
		static List<Suite> _suites;
		return _suites;
	}

	/**
	 * Default constructor
	 * 
	 * @param name The name of the test suite.
	 */
	Suite::Suite (const String &name, void (*&)(), void (*&)()) throw ():
	              name (name),
	              priv (new SuitePrivate)
	{
		suites ().append (this);
	}

	/** Default destructor */
	Suite::~Suite () throw ()
	{
		delete priv;
	}

	/**
	 * Add a test to this suite. This should never be called except by
	 * the constructor for the Test class.
	 * 
	 * @param test The test to add.
	 */
	void
	Suite::add_test (Test *test) throw ()
	{
		priv->tests.append (test);
	}

	/**
	 * Get the list of tests in this suite.
	 * 
	 * @return All tests in this suite, in no particular order.
	 */
	List<Test>
	Suite::get_tests () const throw ()
	{
		return priv->tests;
	}

	/**
	 * Get a list of all test suites.
	 * 
	 * @return A list of all test suites.
	 */
	List<Suite>
	Suite::all_suites () throw ()
	{
		return suites ();
	}

	static
	bool
	matcher (const Suite *key, const void *data)
	{
		return key->name == *static_cast<const String *> (data);
	}

	/**
	 * @brief Find a named suite.
	 * 
	 * @param name The name of the suite.
	 * 
	 * @return The suite with the given name, or NULL if no such
	 *         suite exists.
	 */
	const Suite *
	Suite::find (const String &name) throw ()
	{
		const ListNode<Suite> *node;
		node = all_suites ().find (matcher, &name);

		if (node)
			return node->value;

		return NULL;
	}
}
