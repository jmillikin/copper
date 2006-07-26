#ifndef TEST_H
#define TEST_H

/* For fabs() */
#include <cmath>

/* For formatting error strings */
#include <sstream>

#define TEST_SUITE(NAME) namespace suite_##NAME { \
                           static const char* static_suite_name=#NAME;

#define END_TEST_SUITE }

#define TEST(NAME) class test_##NAME : public UnitTests::Test { \
                   public: \
                     test_##NAME(): UnitTests::Test(#NAME, static_suite_name){} \
                   protected: \
                     virtual void _run() const; \
                   } test_instance_##NAME; \
                   void test_##NAME::_run() const

#include "assertion.h"

namespace UnitTests {

class Test {
  friend class DefaultOutputHandler;
public:
  Test(const std::string& _name, const std::string& _suite_name) throw();
  virtual ~Test(){}

  void pass() const throw();

  void fail(const std::string& message) const throw();

  /** Run the test code in a try/catch */
  void run() const throw();

  /** Run the test code, and abort on uncaught exceptions */
  void run_no_exceptions() const throw();

protected:
  Assertion<std::string> assert(const char* value) const throw(){
    return Assertion<std::string>(value, this);
  }

  Assertion<std::string> assert(char* value) const throw(){
    return Assertion<std::string>(value, this);
  }

  template <class T>
  Assertion<T> assert(const T& value) const throw(){
    return Assertion<T>(value, this);
  }

  /** Run the user's test code */
  virtual void _run() const = 0;

  const std::string name;
  const std::string suite_name;
};

} /* Namespace */

#endif /* TEST_H */
