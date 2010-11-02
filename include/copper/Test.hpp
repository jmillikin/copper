/* test.hpp -- Runs a single unit test
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_HPP
#define COPPER_TEST_HPP

#include <copper/List.hpp>
#include <copper/String.hpp>

namespace Copper {

class TestRun;

class Fixture
{
public:
	virtual void
	Copper_SetUpImpl ();
	
	virtual void
	Copper_TearDownImpl ();
};

class Test
{
public:
	Test (const char name[],
	      const char suite[],
	      const char file_name[],
	      const unsigned int line);
	
	virtual
	~Test ();
	
	static const List<Test> &
	all ();
	
	static Test *
	find (const String &suite_name,
	      const String &test_name);
	
	static List<Test>
	in_suite (const String &suite_name);
	
	void Run (TestRun &);
	void SetUp ();
	void TearDown ();
	
	/* Constant properties */
	const String Name;
	
	const String Suite;
	
	const String FileName;
	
	const unsigned int Line;
	
protected:
	virtual void
	Copper_RunImpl (TestRun &) = 0;
	
	virtual Fixture *
	Copper_GetFixture ();
	
private:
	Test &
	operator= (const Test&);
	
	Test (const Test&);
};

}

#endif /* COPPER_TEST_HPP */
