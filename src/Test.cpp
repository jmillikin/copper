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

#include <copper/Test.hpp>

namespace Copper
{

static TestList &all_tests()
{
	static TestList tests;
	return tests;
}

void Fixture::Copper_SetUpImpl()
{}

void Fixture::Copper_TearDownImpl()
{}

Test::Test
	( const char *name
	, const char *suite
	, const char *file_name
	, const unsigned int line
	)
	: name(String::peek(name))
	, suite(String::peek(suite))
	, file_name(String::peek(file_name))
	, line(line)
{
	all_tests().append(*this);
}

Test::~Test()
{
}

const TestList &Test::all()
{
	return all_tests();
}

void Test::Run(TestRun &run)
{
	SetUp();
	Copper_RunImpl(run);
	TearDown();
}

void Test::SetUp()
{
	Fixture *fixture = Copper_GetFixture();
	if (fixture) { fixture->Copper_SetUpImpl(); }
}

void Test::TearDown()
{
	Fixture *fixture = Copper_GetFixture();
	if (fixture) { fixture->Copper_TearDownImpl(); }
}

Fixture *Test::Copper_GetFixture()
{
	return NULL;
}

class TestList::Node
{
public:
	Node(Test &test)
		: test(&test)
	{}
	
	Test *test;
	Node *next;
};

TestList::TestList()
	: root(NULL)
{
}

TestList::TestList(const TestList &other)
	: root(NULL)
{
	extend(other);
}

TestList::~TestList()
{
	clear();
}

TestList &TestList::operator=(const TestList &other)
{
	clear();
	extend(other);
	return *this;
}

bool TestList::each(iterator &iter, Test **out_test) const
{
	if (not iter.started)
	{
		iter.node = root;
		iter.started = true;
	}
	
	if (iter.node)
	{
		*out_test = iter.node->test;
		iter.node = iter.node->next;
		return true;
	}
	else
	{
		return false;
	}
}

void TestList::append(Test &test)
{
	if (root)
	{
		Node *last = root;
		while (last->next)
		{ last = last->next; }
		
		last->next = new Node(test);
	}
	else
	{
		root = new Node(test);
	}
}

void TestList::extend(const TestList &other)
{
	TestList::iterator iter;
	
	Test *test;
	while (other.each(iter, &test))
	{ append(*test); }
}

void TestList::clear()
{
	Node *node = root, *next;
	root = NULL;
	while (node)
	{
		next = node->next;
		delete node;
		node = next;
	}
}

TestList::iterator::iterator()
	: started(false)
	, node(NULL)
{
}

}
