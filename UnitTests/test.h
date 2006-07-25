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
  Assertion(const T& value, const Test* _test) throw();

  /**
    Assert the two values are equal

    @param expected The expected value of this assertion
  */
  void equals(const T& expected) const throw();

  /**
    Assert that two values are not equal

    @param expected What this assertion is expected not to be
  */
  void not_equal(const T& expected) const throw();

  /** Assert this value is NULL */
  void is_null();

  /** Assert this value is not NULL */
  void not_null();

  /**
    Check that the two values are nearly equal within a certain delta

    @param expected The expected floating-point number
    @param delta The allowable difference between the expected and actual
    values
  */
  void nearly_equals(const T& expected, const T& delta) const throw();

  /**
    Check that the result is greater than some expected value

    @param limit The number the result must be above
  */
  void greater_than(const T& limit) const throw();

  /**
    Check that the result is greater than or equal to some expected value

    @param limit The number the result must be above or equal to
  */
  void greater_than_or_equal(const T& limit) const throw();

  /**
    Check that the result is less than some expected value

    @param limit The number the result must be below
  */
  void less_than(const T& limit) const throw();

  /**
    Check that the result is less than or equal to some expected value

    @param limit The number the result must be below or equal to
  */
  void less_than_or_equal(const T& limit) const throw();

  /**
    Check that the value can be evaluated to the boolean value 'true'
  */
  void is_true() const throw();

  /**
    Check that the value can be evaluated to the boolean value 'false'
  */
  void is_false() const throw();

protected:
  const T& result;
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
  template <class T>
  Assertion<T> assert(const T& value) const throw() {
    return Assertion<T>(value, this);
  }

  /** Run the user's test code */
  virtual void _run() const = 0;

  const std::string name;
  const std::string suite_name;
};

template <class T>
Assertion<T>::Assertion(const T& value, const Test* _test) throw():
  result(value), test(_test) {}

template <class T>
void Assertion<T>::equals(const T& expected) const throw() {
  if (result == expected){
    test->pass();
  }

  else {
    std::stringstream ss;
    ss << "Unequal values: expected '" << expected << "', got '" << result << "'";
    test->fail(ss.str());
  }
}

template <class T>
void Assertion<T>::not_equal(const T& expected) const throw(){
  if (result == expected){
    test->pass();
  }

  else {
    std::stringstream ss;
    ss << "'" << result << "' is equal to '" << expected << "'";
    test->fail(ss.str());
  }
}

template <class T>
void Assertion<T>::is_null(){
  if (result == NULL){
    test->pass();
  }

  else {
    std::stringstream ss;
    ss << "'" << result << "' is not NULL";
    test->fail(ss.str());
  }
}

template <class T>
void Assertion<T>::not_null(){
  if (result != NULL){
    test->pass();
  }

  else {
    std::stringstream ss;
    ss << "'" << result << "' is NULL";
    test->fail(ss.str());
  }
}


template <class T>
void Assertion<T>::nearly_equals(const T& expected, const T& delta) const throw(){
  if (fabs(expected - result) < delta){
    test->pass();
  }

  else {
    std::stringstream ss;
    ss << "Result '" << result << "' is not within '" << delta << "' of '"
      << expected << "'";
    test->fail(ss.str());
  }
}

template <class T>
void Assertion<T>::greater_than(const T& limit) const throw(){
  if (result > limit){
    test->pass();
  }

  else {
    std::stringstream ss;
    ss << "'" << result << "' is not greater than '" << limit << "'";
    test->fail(ss.str());
  }
}

template <class T>
void Assertion<T>::greater_than_or_equal(const T& limit) const throw(){
  if (result >= limit){
    test->pass();
  }

  else {
    std::stringstream ss;
    ss << "'" << result << "' is not greater than or equal to '" << limit
      << "'";
    test->fail(ss.str());
  }
}

template <class T>
void Assertion<T>::less_than(const T& limit) const throw(){
  if (result > limit){
    test->pass();
  }

  else {
    std::stringstream ss;
    ss << "'" << result << "' is not less than '" << limit << "'";
    test->fail(ss.str());
  }
}

template <class T>
void Assertion<T>::less_than_or_equal(const T& limit) const throw(){
  if (result > limit){
    test->pass();
  }

  else {
    std::stringstream ss;
    ss << "'" << result << "' is not less than or equal to '" << limit << "'";
    test->fail(ss.str());
  }
}

template <class T>
void Assertion<T>::is_true() const throw() {
  if (result){
    test->pass();
  }

  else {
    test->fail("Expected to be true, but is false");
  }
}

template <class T>
void Assertion<T>::is_false() const throw() {
  if (!result){
    test->pass();
  }

  else {
    test->fail("Expected to be false, but is true");
  }
}

} /* Namespace */

#endif /* TEST_H */
