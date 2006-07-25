#ifndef TEST_H
#define TEST_H

/* For fabs() */
#include <cmath>

#define TEST_SUITE(NAME) namespace suite_##NAME { \
                           static const char* static_suite_name=#NAME;

#define END_TEST_SUITE }

#define TEST(NAME) class test_##NAME : public UnitTests::Test { \
                   public: \
                     test_##NAME(): UnitTests::Test(#NAME, static_suite_name){} \
                   protected: \
                     virtual void _run() const throw(); \
                   } test_instance_##NAME; \
                   void test_##NAME::_run() const throw()

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
    Assert that the two values are equal

    @param value A value that can be checked for exact equality. For floating
    point equality checking, use @nearly_equals
  */
  void equals(const T& expected) const throw();

  /**
    Check that the two values are nearly equal within a certain delta

    @param A floating-point number
  */
  void nearly_equals(const T& expected, const T& delta) const throw();


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
  Test(const char* _name, const char* _suite_name) throw();
  virtual ~Test(){}

  void pass() const throw();

  void fail(const char* message) const throw();

  /** Run the test code in an optional try/catch */
  void run() const throw();

protected:
  template <class T>
  Assertion<T> Test::assert(const T& value) const throw() {
    return Assertion<T>(value, this);
  }

  /** Run the user's test code */
  virtual void _run() const throw() = 0;

  const char* name;
  const char* suite_name;
};

template <class T>
Assertion<T>::Assertion(const T& value, const Test* _test) throw():
  result(value), test(_test) {}

template <class T>
void Assertion<T>::equals(const T& expected) const throw() {
  if (result == expected){
    // This test has passed
    test->pass();
  }

  else {
    // This test has failed
    test->fail("equals() failed");
  }
}

template <class T>
void Assertion<T>::nearly_equals(const T& expected, const T& delta) const throw() {
  if (fabs(expected - result) < delta){
    test->pass();
  }

  else {
    test->fail("nearly_equals() failed");
  }
}

template <class T>
void Assertion<T>::is_true() const throw() {
  if (result){
    test->pass();
  }

  else {
    test->fail("is_true() failed");
  }
}

template <class T>
void Assertion<T>::is_false() const throw() {
  if (!result){
    test->pass();
  }

  else {
    test->fail("is_false() failed");
  }
}

} /* Namespace */

#endif /* TEST_H */