/* macros.hpp - Preprocessor macros to ease test building
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef COPPER_MACROS_HPP
#define COPPER_MACROS_HPP

#ifdef assert
#undef assert
#endif

/**
  Assert that something is true. If an assertion fails, the test will
  terminate

  @param ASSERTION The Assertion to test
  @param MESSAGE If this parameter is included, it will be used as a
    custom error message
*/

// Early versions of GCC had different syntax for variable arguments
#ifdef __GNUC__
#if __GNUC__ < 3
#define assert(ARGS...) real_assert(ARGS, __LINE__)

#define real_assert(ASSERTION, ARGS...) {\
  Copper::Assertion assertion(ASSERTION, #ASSERTION, ARGS);\
  if (!assertion.passed()) {\
    *bad_assertion = new Copper::Assertion(assertion);\
    return;\
  }\
}
#else /* __GNUC__ is > 3 */
#ifndef ENABLE_VARIADIC_ASSERT
#define ENABLE_VARIADIC_ASSERT 1
#endif /* ENABLE_VARIADIC_ASSERT */
#endif /* __GNUC__ */

#endif /* ifdef __GNUC__ */

#ifndef assert
#ifndef ENABLE_VARIADIC_ASSERT
#if HAVE_VARIADIC_MACROS
#define ENABLE_VARIADIC_ASSERT 1
#endif /* HAVE_VARIADIC_MACROS */
#endif /* ENABLE_VARIADIC_ASSERT */

/* C99 style of variadic macros */
#if ENABLE_VARIADIC_ASSERT

#define assert(...) real_assert(__VA_ARGS__, __LINE__)

#define real_assert(ASSERTION, ...) {\
  Copper::Assertion assertion(ASSERTION, #ASSERTION, __VA_ARGS__);\
  if (!assertion.passed()) {\
    *bad_assertion = new Copper::Assertion(assertion);\
    return;\
  }\
}

#else /* ENABLE_VARIADIC_ASSERT */

#define assert(ASSERTION) {\
  Copper::Assertion assertion(ASSERTION, #ASSERTION, __LINE__);\
  if (!assertion.passed()) {\
    *bad_assertion = new Copper::Assertion(assertion);\
    return;\
  }\
}

#endif /* ENABLE_VARIADIC_ASSERT */
#endif /* assert */

/**
  Used to manually fail a test
*/
#define fail(MESSAGE) \
  *bad_assertion = new Copper::Assertion(false, "", MESSAGE, __LINE__);\
  return;

/**
  Invert the output from an assertion

  @param ASSERTION The Assertion to invert
*/
#define failed(ASSERTION) Copper::failed_func(\
  Copper::Assertion(ASSERTION, #ASSERTION, __LINE__))

/**
  Begin a test suite with the given name

  The reason the namespace is used twice is to allow the use of this macro
  as TEST_SUITE(name) {

  @param NAME The name of the new test suite
*/
#define TEST_SUITE(NAME) \
  namespace suite_namespace_##NAME { \
    static Copper::Suite current_suite(#NAME); \
    static const void (*_set_up)() = 0; \
    static const void (*_tear_down)() = 0; \
  } \
  namespace suite_namespace_##NAME

/**
  Define a new Test with the given name

  @param NAME The name of the new test suite
*/
#define TEST(NAME) \
  class test_##NAME : public Copper::Test { \
  public: \
    test_##NAME(): Copper::Test(#NAME, &current_suite, __FILE__){} \
  protected: \
    void _run(Copper::Assertion** bad_assertion); \
  } test_instance_##NAME; \
  void test_##NAME::_run(Copper::Assertion** bad_assertion)

/**
  Define a new Fixture, with the given name

  @param NAME The name of the new fixture
*/
#define FIXTURE(NAME) namespace fixture_namespace_##NAME

#define SET_UP \
  void set_up(); \
  void (*_set_up)() = set_up; \
  void set_up()

#define TEAR_DOWN \
  void tear_down(); \
  void (*_tear_down)() = tear_down; \
  void tear_down()

/**
  Define a new Test with the given name. The fixture will be used to set up
  or tear down the test.

  @param NAME The name of the new test suite
  @param FIXTURE The Fixture to use for test management
*/
#define FIXTURE_TEST(NAME, FIXTURE) \
  namespace fixture_namespace_##FIXTURE { \
    class test_##NAME : public Copper::Test { \
    public: \
      test_##NAME(): \
        Copper::Test(#NAME, &current_suite, __FILE__) {} \
    protected: \
      void _run(Copper::Assertion** bad_assertion); \
      void set_up(){ \
        if (_set_up) { \
          _set_up(); \
        } \
      } \
      void tear_down(){ \
        if (_tear_down) { \
          _tear_down(); \
        } \
      } \
    } test_instance_##NAME; \
  } \
  void fixture_namespace_##FIXTURE::test_##NAME::_run( \
    Copper::Assertion** bad_assertion)

#endif /* COPPER_MACROS_HPP */
