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
#define COPPER_ASSERT(ASSERTION) Copper::do_assert (ASSERTION, #ASSERTION, __FILE__, __LINE__)

/**
 * When this macro is called, it will force the test to fail.
 * 
 * @param MESSAGE The error message to fail with.
 */
#define COPPER_FAIL(MESSAGE) Copper::do_fail_test (#MESSAGE, __FILE__, __LINE__)

/**
 * Begins a test suite with the given name.
 * 
 * @param NAME The name of the new test suite.
 */
#define COPPER_SUITE(NAME) \
	namespace _copper_suite_namespace_##NAME \
	{ \
		COPPER_FUNCATTR_UNUSED static void (*_copper_set_up_func) () = 0; \
		COPPER_FUNCATTR_UNUSED static void (*_copper_tear_down_func) () = 0; \
		static const char _copper_current_suite[] = #NAME; \
	} \
	namespace _copper_suite_namespace_##NAME

/**
 * Defines a new test with the given name.
 * 
 * @param NAME The name of the new test.
 */
#define COPPER_TEST(NAME) \
	class _copper_test_##NAME : public Copper::Test \
	{ \
	public: \
		_copper_test_##NAME(): Copper::Test (#NAME, _copper_current_suite, \
		                             __FILE__, __LINE__){} \
	protected: \
		void run (); \
	} _copper_instance_test_##NAME; \
	void _copper_test_##NAME::run ()

/**
 * Define a new fixture, with the given name.
 * 
 * @param NAME The name of the new fixture.
 */
#define COPPER_FIXTURE(NAME) namespace _copper_fixture_namespace_##NAME

/**
 * Defines a function that should be called whenever the fixture containing
 * it is initialized.
 */
#define COPPER_SET_UP \
	void _copper_set_up (); \
	void (*_copper_set_up_func) () = _copper_set_up; \
	void _copper_set_up ()

/**
 * Defines a function that should be called whenever the fixture containing
 * it is de-initialized.
 */
#define COPPER_TEAR_DOWN \
	void _copper_tear_down (); \
	void (*_copper_tear_down_func) () = _copper_tear_down; \
	void _copper_tear_down ()

/**
 * Define a new test with the given name. The fixture will be used to set up
 * or tear down the test.
 * 
 * @param NAME The name of the new test suite.
 * @param FIXTURE The fixture to use for test management.
 */
#define COPPER_FIXTURE_TEST(NAME, FIXTURE) \
	namespace _copper_fixture_namespace_##FIXTURE \
	{ \
		class _copper_test_##NAME : public Copper::Test \
		{ \
		public: \
			_copper_test_##NAME(): Copper::Test (\
				#NAME, _copper_current_suite,  __FILE__, \
				__LINE__) {} \
			void set_up () { \
				if (_copper_set_up_func) \
					_copper_set_up_func (); \
			} \
			void tear_down () { \
				if (_copper_tear_down_func) \
					_copper_tear_down_func (); \
			} \
			void run() \
			{ \
				set_up (); \
				_run (); \
				tear_down (); \
			} \
		protected: \
			void _run (); \
		} _copper_instance_test_##NAME; \
	} \
	void _copper_fixture_namespace_##FIXTURE::_copper_test_##NAME::_run ()

inline void _copper_throws_cleanup (...) {}

/**
 * Used to check if some code throws a certain type of exception.
 * 
 * @param TYPE The type of exception that should be thrown.
 * @param CODE Some valid C++ code. This code will be executed, and any
 *             exceptions it throws will be checked against TYPE.
 */
#define throws(TYPE, CODE) ); \
{ bool _copper_exception_thrown = false; \
	try \
	{ \
		CODE; \
	} \
	catch (const TYPE&) \
	{ \
		_copper_exception_thrown = true; \
	} \
	if (!_copper_exception_thrown) \
	{ \
		Copper::do_fail_test ("throws ("#TYPE", "#CODE")", \
		                      "\""#CODE"\" didn't throw an exception of type \""#TYPE"\"", \
		                      __FILE__, __LINE__); \
	} \
} _throws_cleanup (0

#endif /* COPPER_MACROS_HPP */
