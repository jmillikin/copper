/* test.hpp -- Runs a single unit test
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef TEST_HPP
#define TEST_HPP

#include "assertion.hpp"
#include "suite.hpp"

namespace UnitTests {

class OutputHandler;

class Test {
public:
  Test(
    const char* name,
    Suite* suite,
    const char* file_name) throw ();
  virtual ~Test();

  /** Run the test */
  Assertion* run();

  /** The name of this test */
  const char* name;

  /** The suite this test is part of */
  const Suite* suite;

  /** The file this test's implementation is in */
  const char* file_name;

protected:
  /** Run the user's test code */
  virtual void _run(UnitTests::Assertion** bad_assertion) = 0;

  /** Used to set up this test's fixture, if it exists */
  virtual void set_up() = 0;

  /** Used to tear down this test's fixture, if it exists */
  virtual void tear_down() = 0;
};

} /* Namespace */

// Disable warnings about throw specifications in VS 2003
#ifdef _MSC_VER
#pragma warning(disable: 4290)
#endif

// The reason the namespace is used twice is to allow the use of this macro
// as TEST_SUITE(name) {
#define TEST_SUITE(NAME) \
  namespace suite_namespace_##NAME { \
    static UnitTests::Suite current_suite(#NAME); } \
  namespace suite_namespace_##NAME

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

#define FIXTURE(NAME) \
  class fixture_##NAME : public UnitTests::Fixture { \
    public: \
      fixture_##NAME(): UnitTests::Fixture(){} \
    protected:

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

#endif /* TEST_HPP */
