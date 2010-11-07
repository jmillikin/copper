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

static List<Test> &
all_tests()
{
	static List<Test> _tests;
	return _tests;
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
	all_tests().append(this);
}

Test::~Test()
{
}

const List<Test> &Test::all()
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
}
