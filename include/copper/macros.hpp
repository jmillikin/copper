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

#ifndef COPPER_MACROS_HPP
#define COPPER_MACROS_HPP

#define COPPER_SUITE(NAME) \
	namespace Copper_Suite_##NAME \
	{ static const char Copper_CurrentSuiteName[] = #NAME; } \
	namespace Copper_Suite_##NAME

#define COPPER_TEST(NAME) \
	class Copper_Test_##NAME : public Copper::Test \
	{ \
	public: \
		Copper_Test_##NAME(): Copper::Test ( \
			#NAME, Copper_CurrentSuiteName, \
			__FILE__, __LINE__){} \
	protected: \
		void Copper_RunImpl (Copper::TestRun &); \
	} Copper_TestInstance_##NAME; \
	void Copper_Test_##NAME::Copper_RunImpl (Copper::TestRun &Copper_TestRun)

#define COPPER_FIXTURE(NAME) \
	struct Copper_Fixture_##NAME : public Copper::Fixture

#define COPPER_SET_UP virtual void Copper_SetUpImpl ()

#define COPPER_TEAR_DOWN virtual void Copper_TearDownImpl ()

#define COPPER_FIXTURE_TEST(NAME, FIXTURE) \
	class Copper_Test_##NAME : public Copper_Fixture_##FIXTURE, \
	                           public Copper::Test \
	{ \
	public: \
		Copper_Test_##NAME(): Copper::Test ( \
			#NAME, Copper_CurrentSuiteName, \
			__FILE__, __LINE__){} \
	protected: \
		Copper::Fixture *Copper_GetFixture () { return this; } \
		void Copper_RunImpl (Copper::TestRun &); \
	} Copper_TestInstance_##NAME; \
	void Copper_Test_##NAME::Copper_RunImpl (Copper::TestRun &Copper_TestRun)

#define COPPER_ASSERT(ASSERTION) Copper_TestRun.assert ((ASSERTION), #ASSERTION, __FILE__, __LINE__)

#define COPPER_FAIL(MESSAGE) Copper_TestRun.fail (MESSAGE, __FILE__, __LINE__)

#define COPPER_ASSERT_THROWS(TYPE, CODE) \
	do { \
		bool Copper_ExceptionThrown = false; \
		try { CODE } \
		catch (const TYPE &) { Copper_ExceptionThrown = true; } \
		if (!Copper_ExceptionThrown) { \
			Copper_TestRun.fail_throws(#TYPE, #CODE, __FILE__, __LINE__) \
		}} while (0)

#endif
