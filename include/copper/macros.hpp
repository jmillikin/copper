/* macros.hpp - Preprocessor macros to ease test building
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef assert
#undef assert
#endif

#ifndef COPPER_MACROS_HPP
#define COPPER_MACROS_HPP

/**
  Assert that something is true. If an assertion fails, the test will
  terminate

  @param ASSERTION The Assertion to test
  @param MESSAGE If this parameter is included, it will be used as a
    custom error message
*/
#define assert(ASSERTION) Copper::do_assert(ASSERTION, #ASSERTION, __LINE__)

/**
  Used to manually fail a test
*/
#define fail_test(MESSAGE) Copper::do_fail_test (#MESSAGE, __LINE__)

/**
  Invert the output from an assertion

  @param ASSERTION The Assertion to invert
*/
#define failed(ASSERTION) Copper::failed_func(                                 \
  Copper::Assertion(ASSERTION, #ASSERTION, __LINE__))

/**
  Begin a test suite with the given name

  The reason the namespace is used twice is to allow the use of this macro
  as TEST_SUITE(name) {

  @param NAME The name of the new test suite
*/
#define TEST_SUITE(NAME) TEST_SUITE2(NAME, __LINE__)

#define TEST_SUITE2(NAME, LINE) TEST_SUITE3(NAME, LINE)

#define TEST_SUITE3(NAME, LINE)                                                \
  namespace suite_namespace_##NAME##_##LINE {                                  \
    static void (*_set_up)() = 0;                                              \
    static void (*_tear_down)() = 0;                                           \
    static Copper::Suite current_suite(#NAME, _set_up, _tear_down);            \
  }                                                                            \
  namespace suite_namespace_##NAME##_##LINE

/**
  Define a new Test with the given name

  @param NAME The name of the new test suite
*/
#define TEST(NAME) TEST2(NAME, __LINE__)

#define TEST2(NAME, LINE) TEST3(NAME, LINE)

#define TEST3(NAME, LINE)                                                      \
  class test_##NAME##_##LINE : public Copper::Test {                           \
  public:                                                                      \
    test_##NAME##_##LINE(): Copper::Test(#NAME, &current_suite, __FILE__){}    \
  protected:                                                                   \
    void run();                                                                \
  } test_instance_##NAME##_##LINE;                                             \
  void test_##NAME##_##LINE::run()

/**
  Define a new Fixture, with the given name

  @param NAME The name of the new fixture
*/
#define FIXTURE(NAME) namespace fixture_namespace_##NAME

#define SET_UP                                                                 \
  void __set_up();                                                             \
  void (*_set_up)() = __set_up;                                                \
  void __set_up()

#define TEAR_DOWN                                                              \
  void __tear_down();                                                          \
  void (*_tear_down)() = __tear_down;                                          \
  void __tear_down()

/**
  Define a new Test with the given name. The fixture will be used to set up
  or tear down the test.

  @param NAME The name of the new test suite
  @param FIXTURE The Fixture to use for test management
*/
#define FIXTURE_TEST(NAME, FIXTURE) FIXTURE_TEST2(NAME, FIXTURE, __LINE__)

#define FIXTURE_TEST2(NAME, FIXTURE, LINE) FIXTURE_TEST3(NAME, FIXTURE, LINE)

#define FIXTURE_TEST3(NAME, FIXTURE, LINE)                                     \
  namespace fixture_namespace_##FIXTURE {                                      \
    class test_##NAME##_##LINE : public Copper::Test {                         \
    public:                                                                    \
      test_##NAME##_##LINE():                                                  \
        Copper::Test(#NAME, &current_suite, __FILE__) {}                       \
      void set_up () { if (_set_up) _set_up(); }                               \
      void tear_down () { if (_tear_down) _tear_down(); }                      \
      void run() {                                                             \
        set_up();                                                              \
        _run();                                                                \
        tear_down();                                                           \
      }                                                                        \
    protected:                                                                 \
      void _run();                                                             \
    } test_instance_##NAME##_##LINE;                                           \
  }                                                                            \
  void fixture_namespace_##FIXTURE::test_##NAME##_##LINE::_run()

#define throws(TYPE, CODE) \
  Copper::AssertionResult().fail("throws() cannot be used when exceptions are disabled")

#endif /* COPPER_MACROS_HPP */
