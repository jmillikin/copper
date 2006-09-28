/* macros.hpp - Preprocessor macros to ease test building
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef MACROS_HPP
#define MACROS_HPP

/**
  Assert that something is true. If an assertion fails, the test will
  terminate

  @param ASSERTION The Assertion to test
*/
#define assert(ASSERTION) {\
  UnitTests::Assertion assertion(ASSERTION, #ASSERTION, __LINE__);\
  if (!assertion.passed()) {\
    *bad_assertion = new UnitTests::Assertion(assertion);\
    return;\
  }\
}

/**
  Invert the output from an assertion

  @param ASSERTION The Assertion to invert
*/
#define failed(ASSERTION) UnitTests::failed_func(\
  UnitTests::Assertion(ASSERTION, #ASSERTION, __LINE__))

/**
  Check that some code throws an exception

  @param CODE The code to run
  @param EXCEPTION_TYPE The type of exception to check for
*/
#define assert_throws(CODE, EXCEPTION_TYPE) \
  try {\
    CODE;\
    UnitTests::Assertion assertion(\
      UnitTests::AssertionResult().fail(#CODE" threw no exceptions"), \
      "assert_throws("#CODE", "#EXCEPTION_TYPE")", __LINE__);\
    if (!assertion.passed()) {\
      *bad_assertion = new UnitTests::Assertion(assertion);\
      return;\
    }\
  }\
  catch (const EXCEPTION_TYPE&) {}

/**
  Begin a test suite with the given name

  The reason the namespace is used twice is to allow the use of this macro
  as TEST_SUITE(name) {

  @param NAME The name of the new test suite
*/
#define TEST_SUITE(NAME) \
  namespace suite_namespace_##NAME { \
    static UnitTests::Suite current_suite(#NAME); } \
  namespace suite_namespace_##NAME

/**
  Define a new Test with the given name

  @param NAME The name of the new test suite
*/
#define TEST(NAME) \
  class test_##NAME : public UnitTests::Test { \
  public: \
    test_##NAME(): UnitTests::Test(#NAME, &current_suite, __FILE__){} \
  protected: \
    void set_up(){} \
    void tear_down(){} \
    void _run(UnitTests::Assertion** bad_assertion); \
  } test_instance_##NAME; \
  void test_##NAME::_run(UnitTests::Assertion** bad_assertion)

/**
  Define a new Fixture, with the given name

  @param NAME The name of the new fixture
*/
#define FIXTURE(NAME) \
  class fixture_##NAME : public UnitTests::Fixture { \
    public: \
      fixture_##NAME(): UnitTests::Fixture(){} \
    protected:

/**
  Define a new Test with the given name. The fixture will be used to set up
  or tear down the test.

  @param NAME The name of the new test suite
  @param FIXTURE The Fixture to use for test management
*/
#define FIXTURE_TEST(NAME, FIXTURE) \
  class test_##NAME : public UnitTests::Test, public fixture_##FIXTURE { \
  public: \
    test_##NAME(): \
      UnitTests::Test(#NAME, &current_suite, __FILE__), \
      fixture_##FIXTURE() \
      {} \
  protected: \
    void _run(UnitTests::Assertion** bad_assertion); \
    void set_up(){ \
      fixture_##FIXTURE::set_up(); \
    } \
    void tear_down(){ \
      fixture_##FIXTURE::tear_down(); \
    } \
  } test_instance_##NAME; \
  void test_##NAME::_run(UnitTests::Assertion** bad_assertion)

#endif /* MACROS_HPP */
