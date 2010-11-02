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

void Fixture::Copper_SetUpImpl()
{}

void Fixture::Copper_TearDownImpl()
{}

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

	            Name (String::FromStatic (name)),
	            Suite (String::FromStatic (suite)),
	            FileName (String::FromStatic (file_name)),
	            Line (line)
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

	void
	Test::Run (TestRun &run)
	{
		SetUp ();
		Copper_RunImpl (run);
		TearDown ();
	}
	
	void
	Test::SetUp ()
	{
		Fixture *fixture = Copper_GetFixture ();
		if (fixture) { fixture->Copper_SetUpImpl (); }
	}
	
	void
	Test::TearDown ()
	{
		Fixture *fixture = Copper_GetFixture ();
		if (fixture) { fixture->Copper_TearDownImpl (); }
	}
	
	Fixture *
	Test::Copper_GetFixture ()
	{
		return NULL;
	}
}
