// Copyright (C) 2006-2010 John Millikin <jmillikin@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef COPPER_TEST_HPP
#define COPPER_TEST_HPP

#include <copper/String.hpp>

namespace Copper {

class TestRun;
class TestList;

class Fixture
{
public:
	virtual void Copper_SetUpImpl();
	
	virtual void Copper_TearDownImpl();
};

class Test
{
public:
	Test
		( const char *name
		, const char *suite
		, const char *file_name
		, const unsigned int line
		);
	
	virtual ~Test ();
	
	static const TestList &all();
	
	void Run(TestRun &);
	void SetUp();
	void TearDown();
	
	const String name;
	const String suite;
	const String file_name;
	const unsigned int line;
	
protected:
	virtual void Copper_RunImpl(TestRun &) = 0;
	
	virtual Fixture *Copper_GetFixture();
};

class TestList
{
public:
	class iterator;
	
	TestList();
	TestList(const TestList &);
	~TestList();
	
	TestList &operator=(const TestList &);
	
	bool each(iterator &, Test **) const;
	
	void append(Test &);
	void extend(const TestList &);
	void clear();
	
private:
	class Node;
	Node *root;
	
public:
	friend class iterator;
	class iterator
	{
	public:
		iterator();
	private:
		friend class TestList;
		bool started;
		TestList::Node *node;
	};
	
};

}

#endif
