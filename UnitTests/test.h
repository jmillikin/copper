#ifndef TEST_H
#define TEST_H

/* For fabs() */
#include <cmath>

/* For formatting error strings */
#include <sstream>

/* Block any macro shenanigans from the standard library */
#ifdef assert
#undef assert
#endif

#define TEST_SUITE(NAME) \
  namespace suite_##NAME { \
    static const char* static_suite_name=#NAME;

#define TEST(NAME) \
  class test_##NAME : public UnitTests::Test { \
  public: \
    test_##NAME(): UnitTests::Test(#NAME, static_suite_name, __LINE__){} \
  protected: \
    void set_up(){} \
    void tear_down(){} \
    virtual void _run(); \
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
      UnitTests::Test(#NAME, static_suite_name, __LINE__), \
      fixture_##FIXTURE() \
      {} \
  protected: \
    virtual void _run(); \
    virtual void set_up(){ \
      fixture_##FIXTURE::set_up(); \
    } \
    virtual void tear_down(){ \
      fixture_##FIXTURE::tear_down(); \
    } \
  } test_instance_##NAME; \
  void test_##NAME::_run(){

#include "assertion.h"

namespace UnitTests {

class FailureException;

class Test {
public:
  Test(const std::string& name,
    const std::string& suite_name,
    const unsigned int line_number) throw ();
  virtual ~Test(){}

  /** Run the test code in a try/catch */
  void run() throw (FailureException);

  /** Run the test code, and abort on uncaught exceptions */
  void run_no_exceptions() throw (FailureException);

  /** Get a string to represent this test */
  std::string get_string() const throw ();

protected:
  Assertion<std::string> assert(const char* value) throw () {
    return Assertion<std::string>(value, this);
  }

  Assertion<std::string> assert(char* value) throw () {
    return Assertion<std::string>(value, this);
  }

  template <class T>
  Assertion<T> assert(const T& value) throw () {
    return Assertion<T>(value, this);
  }

  /** Run the user's test code */
  virtual void _run() = 0;

  bool test_failed;

  const std::string test_name;
  const std::string test_suite_name;
  const unsigned int test_line_number;

  /** Used to set up this test's fixture, if it exists */
  virtual void set_up() = 0;

  /** Used to tear down this test's fixture, if it exists */
  virtual void tear_down() = 0;
};

} /* Namespace */

#endif /* TEST_H */
