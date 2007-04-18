/* suite.cpp -- Groups tests into logical groups
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "export.hpp"
#include "suite.hpp"

namespace Copper
{
	/** @class Suite
	 */

	/** @var Suite::tests
	 * All tests in this suite, in no particular order.
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
	COPPER_EXPORT
	Suite::Suite (const String &name, void (*&)(), void (*&)()) throw ():
	              name (name)
	{
		suites ().append (this);
	}

	/** Default destructor */
	COPPER_EXPORT
	Suite::~Suite () throw ()
	{
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
		tests.append (test);
	}

	/**
	 * Get the list of tests in this suite.
	 * 
	 * @return All tests in this suite, in no particular order.
	 */
	COPPER_EXPORT
	List<Test>
	Suite::get_tests () const throw ()
	{
		return tests;
	}

	/**
	 * Get a list of all test suites.
	 * 
	 * @return A list of all test suites.
	 */
	COPPER_EXPORT
	List<Suite>
	Suite::all_suites () throw ()
	{
		return suites ();
	}
}
