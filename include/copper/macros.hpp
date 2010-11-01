/* macros.hpp -- Preprocessor macros to ease test building
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_MACROS_HPP
#define COPPER_MACROS_HPP

/**
 * Begins a test suite with the given name.
 * 
 * @param NAME The name of the new test suite.
**/
#define COPPER_SUITE(NAME) \
	namespace Copper_Suite_##NAME \
	{ static const char Copper_CurrentSuiteName[] = #NAME; } \
	namespace Copper_Suite_##NAME

/**
 * Defines a new test with the given name.
 * 
 * @param NAME The name of the new test.
**/
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

/**
 * Define a new fixture, with the given name.
 * 
 * @param NAME The name of the new fixture.
**/
#define COPPER_FIXTURE(NAME) \
	struct Copper_Fixture_##NAME : public Copper::Fixture

/**
 * Defines a function that should be called whenever the fixture containing
 * it is initialized.
**/
#define COPPER_SET_UP virtual void Copper_SetUpImpl ()

/**
 * Defines a function that should be called whenever the fixture containing
 * it is de-initialized.
**/
#define COPPER_TEAR_DOWN virtual void Copper_TearDownImpl ()

/**
 * Define a new test with the given name. The fixture will be used to set up
 * or tear down the test.
 * 
 * @param NAME The name of the new test suite.
 * @param FIXTURE The fixture to use for test management.
**/
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

/**
 * Assert that something is true. If an assertion fails, the test will
 * terminate.
 * 
 * @param ASSERTION The assertion to test.
**/
#define COPPER_ASSERT(ASSERTION) \
	do { \
		if (!(Copper_TestRun.Assert (ASSERTION, #ASSERTION, __FILE__, __LINE__))) { \
			return; }} while (0)

/**
 * When this macro is called, it will force the test to fail.
 * 
 * @param MESSAGE The error message to fail with.
**/
#define COPPER_FAIL(MESSAGE) \
	do { \
		if (!(Copper_TestRun.Fail (#MESSAGE, __FILE__, __LINE__))) { \
			return; }} while (0)

/**
 * Used to check if some code throws a certain type of exception.
 * 
 * @param TYPE The type of exception that should be thrown.
 * @param CODE Some valid C++ code. This code will be executed, and any
 *             exceptions it throws will be checked against TYPE.
**/
#define COPPER_ASSERT_THROWS(TYPE, CODE) \
	do { \
		bool Copper_ExceptionThrown = false; \
		try { CODE } \
		catch (const TYPE &) { Copper_ExceptionThrown = true; } \
		if (!Copper_ExceptionThrown) { \
			if (!(Copper_TestRun.AssertThrowsFailed (#TYPE, #CODE, __FILE__, __LINE__))) { \
				return; }}} while (0)

#endif
