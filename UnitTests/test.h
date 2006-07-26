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
    test_##NAME(): UnitTests::Test(#NAME, static_suite_name){} \
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
      UnitTests::Test(#NAME, static_suite_name, true), \
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

class Test {
  friend class DefaultOutputHandler;
public:
  Test(const std::string& _name,
    const std::string& _suite_name = "",
    bool has_fixture = false) throw();
  virtual ~Test(){}

  void pass() const throw();

  void fail(const std::string& message) throw();

  /** Run the test code in a try/catch */
  void run() throw();

  /** Run the test code, and abort on uncaught exceptions */
  void run_no_exceptions() throw();

protected:
  Assertion<std::string> assert(const char* value) throw(){
    return Assertion<std::string>(value, this);
  }

  Assertion<std::string> assert(char* value) throw(){
    return Assertion<std::string>(value, this);
  }

  template <class T>
  Assertion<T> assert(const T& value) throw(){
    return Assertion<T>(value, this);
  }

  /** Run the user's test code */
  virtual void _run() = 0;

  bool failed;

  const std::string name;
  const std::string suite_name;

  /** Used to set up this test's fixture, if it exists */
  virtual void set_up() = 0;

  /** Used to tear down this test's fixture, if it exists */
  virtual void tear_down() = 0;

  bool has_fixture;
};

} /* Namespace */

#endif /* TEST_H */
