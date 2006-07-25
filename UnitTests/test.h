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

namespace UnitTests {

class Test;

template <class T>
class Assertion {
public:
  /**
    Create an assertion

    @param value The value to assert against
  */
  Assertion(const T& value, const Test* _test) throw():
    result(value), test(_test){}

  /**
    Assert the two values are equal

    @param expected The expected value of this assertion
  */
  void equals(const T& expected) const throw(){
    if (result == expected){
      pass();
    }

    else {
      std::stringstream ss;
      ss << "Unequal values: expected '" << expected << "', got '" << result << "'";
      fail(ss.str());
    }
  }

  /**
    Assert that two values are not equal

    @param expected What this assertion is expected not to be
  */
  void not_equal(const T& expected) const throw(){
    if (result == expected){
      pass();
    }

    else {
      std::stringstream ss;
      ss << "'" << result << "' is equal to '" << expected << "'";
      fail(ss.str());
    }
  }

  /** Assert this value is NULL */
  void is_null(){
    if (result == NULL){
      pass();
    }

    else {
      std::stringstream ss;
      ss << "'" << result << "' is not NULL";
      fail(ss.str());
    }
  }

  /** Assert this value is not NULL */
  void not_null(){
    if (result != NULL){
      pass();
    }

    else {
      std::stringstream ss;
      ss << "'" << result << "' is NULL";
      fail(ss.str());
    }
  }

  /**
    Check that the two values are nearly equal within a certain delta

    @param expected The expected floating-point number
    @param delta The allowable difference between the expected and actual
    values
  */
  void nearly_equals(const T& expected, const T& delta) const throw(){
    if (fabs(expected - result) < delta){
      pass();
    }

    else {
      std::stringstream ss;
      ss << "Result '" << result << "' is not within '" << delta << "' of '"
        << expected << "'";
      fail(ss.str());
    }
  }

  /**
    Check that the result is greater than some expected value

    @param limit The number the result must be above
  */
  void greater_than(const T& limit) const throw(){
    if (result > limit){
      pass();
    }

    else {
      std::stringstream ss;
      ss << "'" << result << "' is not greater than '" << limit << "'";
      fail(ss.str());
    }
  }

  /**
    Check that the result is greater than or equal to some expected value

    @param limit The number the result must be above or equal to
  */
  void greater_than_or_equal(const T& limit) const throw(){
    if (result >= limit){
      pass();
    }

    else {
      std::stringstream ss;
      ss << "'" << result << "' is not greater than or equal to '" << limit
        << "'";
      fail(ss.str());
    }
  }

  /**
    Check that the result is less than some expected value

    @param limit The number the result must be below
  */
  void less_than(const T& limit) const throw(){
    if (result > limit){
      pass();
    }

    else {
      std::stringstream ss;
      ss << "'" << result << "' is not less than '" << limit << "'";
      fail(ss.str());
    }
  }

  /**
    Check that the result is less than or equal to some expected value

    @param limit The number the result must be below or equal to
  */
  void less_than_or_equal(const T& limit) const throw(){
    if (result > limit){
      pass();
    }

    else {
      std::stringstream ss;
      ss << "'" << result << "' is not less than or equal to '" << limit << "'";
      fail(ss.str());
    }
  }

  /**
    Check that the value can be evaluated to the boolean value 'true'
  */
  void is_true() const throw(){
    if (result){
      pass();
    }

    else {
      fail("Expected to be true, but is false");
    }
  }

  /**
    Check that the value can be evaluated to the boolean value 'false'
  */
  void is_false() const throw(){
    if (!result){
      pass();
    }

    else {
      fail("Expected to be false, but is true");
    }
  }

protected:
  void fail(const std::string& message) const throw();
  void pass() const throw();

  const T result;
  const Test* test;
};

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
    return assert(value);
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

template <class T>
void Assertion<T>::pass() const throw(){
  test->pass();
}

template <class T>
void Assertion<T>::fail(const std::string& message) const throw(){
  test->fail(message);
}

} /* Namespace */

#endif /* TEST_H */
