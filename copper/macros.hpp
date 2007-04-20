/* macros.hpp -- Preprocessor macros to ease test building
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#ifndef COPPER_MACROS_HPP
#define COPPER_MACROS_HPP

/**
 * Assert that something is true. If an assertion fails, the test will
 * terminate.
 * 
 * @param ASSERTION The assertion to test.
 */
#define ASSERT(ASSERTION) Copper::do_assert (ASSERTION, #ASSERTION, __FILE__, __LINE__)

/**
 * When this macro is called, it will force the test to fail.
 * 
 * @param MESSAGE The error message to fail with.
 */
#define fail_test(MESSAGE) Copper::do_fail_test (#MESSAGE, __FILE__, __LINE__)

/**
 * Inverts the output from an assertion.
 * 
 * @param ASSERTION The assertion to invert.
 */
#define failed(ASSERTION) Copper::do_failed (ASSERTION, #ASSERTION)

/**
 * Begins a test suite with the given name.
 * 
 * @param NAME The name of the new test suite.
 */
#define TEST_SUITE(NAME) \
	namespace suite_namespace_##NAME \
	{ \
		COPPER_UNUSED static const void (*_copper_set_up) () = 0; \
		COPPER_UNUSED static const void (*_copper_tear_down) () = 0; \
		static const char _copper_current_suite[] = #NAME; \
	} \
	namespace suite_namespace_##NAME

/**
 * Defines a new test with the given name.
 * 
 * @param NAME The name of the new test.
 */
#define TEST(NAME) \
	class test_##NAME : public Copper::Test \
	{ \
	public: \
		test_##NAME(): Copper::Test (#NAME, _copper_current_suite, \
		                             __FILE__, __LINE__){} \
	protected: \
		void run (); \
	} test_instance_##NAME; \
	void test_##NAME::run ()

/**
 * Define a new fixture, with the given name.
 * 
 * @param NAME The name of the new fixture.
 */
#define FIXTURE(NAME) namespace fixture_namespace_##NAME

/**
 * Defines a function that should be called whenever the fixture containing
 * it is initialized.
 */
#define SET_UP \
	void __copper_set_up (); \
	void (*_copper_set_up) () = __copper_set_up; \
	void __copper_set_up ()

/**
 * Defines a function that should be called whenever the fixture containing
 * it is de-initialized.
 */
#define TEAR_DOWN \
	void __copper_tear_down (); \
	void (*_copper_tear_down) () = __copper_tear_down; \
	void __copper_tear_down ()

/**
 * Define a new test with the given name. The fixture will be used to set up
 * or tear down the test.
 * 
 * @param NAME The name of the new test suite.
 * @param FIXTURE The fixture to use for test management.
 */
#define FIXTURE_TEST(NAME, FIXTURE) \
	namespace fixture_namespace_##FIXTURE \
	{ \
		class test_##NAME : public Copper::Test \
		{ \
		public: \
			test_##NAME(): Copper::Test (#NAME, \
			                             _copper_current_suite, \
			                             __FILE__, \
			                             __LINE__) {} \
			void set_up () { \
				if (_copper_set_up) \
					_copper_set_up (); \
			} \
			void tear_down () { \
				if (_copper_tear_down) \
					_copper_tear_down (); \
			} \
			void run() \
			{ \
				set_up (); \
				_run (); \
				tear_down (); \
			} \
		protected: \
			void _run (); \
		} test_instance_##NAME; \
	} \
	void fixture_namespace_##FIXTURE::test_##NAME::_run ()

inline void __throws_cleanup (...) {}

/**
 * Used to check if some code throws a certain type of exception.
 * 
 * @param TYPE The type of exception that should be thrown.
 * @param CODE Some valid C++ code. This code will be executed, and any
 *             exceptions it throws will be checked against TYPE.
 */
#define throws(TYPE, CODE) ); \
{ bool __copper_exception_thrown = false; \
	try \
	{ \
		CODE; \
	} \
	catch (const TYPE&) \
	{ \
		__copper_exception_thrown = true; \
	} \
	if (!__copper_exception_thrown) \
	{ \
		Copper::do_fail_test ("throws ("#TYPE", "#CODE")", \
		                      "\""#CODE"\" didn't throw an exception of type \""#TYPE"\"", \
		                      __FILE__, __LINE__); \
	} \
} __throws_cleanup (0

#endif /* COPPER_MACROS_HPP */
