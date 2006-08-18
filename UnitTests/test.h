#ifndef TEST_H
#define TEST_H

#include "assertion.h"

namespace UnitTests {

class FailureException;

class Test {
public:
  Test(const std::string& name,
    const std::string& suite_name) throw ();
  virtual ~Test();

  /** Run the test */
  void run();

  const std::string name;
  const std::string suite_name;

protected:
  /** Run the user's test code */
  virtual void _run() = 0;

  /** Used to set up this test's fixture, if it exists */
  virtual void set_up() = 0;

  /** Used to tear down this test's fixture, if it exists */
  virtual void tear_down() = 0;
};

} /* Namespace */

// Disable warnings about throw specifications in VS 2003
#pragma warning(disable: 4290)

#define TEST_SUITE(NAME) \
  namespace suite_##NAME { \
    static const char* static_suite_name=#NAME;

#define TEST(NAME) \
  class test_##NAME : public UnitTests::Test { \
  public: \
    test_##NAME(): UnitTests::Test(#NAME, static_suite_name){} \
  protected: \
    void set_up(){} \
    void tear_down(){} \
    void _run(); \
  } test_instance_##NAME; \
  void test_##NAME::_run(){

#define FIXTURE(NAME) \
  class fixture_##NAME : public UnitTests::Fixture { \
    public: \
      fixture_##NAME(): UnitTests::Fixture(){} \
    protected:

#define FIXTURE_TEST(NAME, FIXTURE) \
  class test_##NAME : public UnitTests::Test, public fixture_##FIXTURE { \
  public: \
    test_##NAME(): \
      UnitTests::Test(#NAME, static_suite_name), \
      fixture_##FIXTURE() \
      {} \
  protected: \
    void _run(); \
    void set_up(){ \
      fixture_##FIXTURE::set_up(); \
    } \
    void tear_down(){ \
      fixture_##FIXTURE::tear_down(); \
    } \
  } test_instance_##NAME; \
  void test_##NAME::_run(){

#endif /* TEST_H */
