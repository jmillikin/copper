#ifndef ASSERTION_H
#define ASSERTION_H

/* For fabs() */
#include <cmath>

/* For formatting error strings */
#include <sstream>

namespace UnitTests {

class Test;

/**
  Base class of Assertion. By separating this out, the implementations of
  fail() and pass() can be placed in a separate file
*/
class BaseAssertion {
public:
  /**
    Default constructor

    @param test The test this assertion was created in
  */
  BaseAssertion(Test* test) throw();

protected:
  /** Cause this assertion to fail, with a message */
  void fail(const std::string& message) throw();

  /** The test this assertion was created in */
  Test* test;
};

template <class T>
class Assertion : public BaseAssertion {
public:
  /**
    Create an assertion

    @param value The value to assert against
    param test The test this assertion was created in
  */
  Assertion(const T& value, Test* test) throw():
    BaseAssertion(test), result(value){}

  /**
    Assert the two values are equal

    @param expected The expected value of this assertion
  */
  void equals(const T& expected) throw(){
    if (result != expected){
      std::stringstream ss;
      ss << "Unequal values: expected '" << expected << "', got '" << result << "'";
      fail(ss.str());
    }
  }

  /**
    Assert that two values are not equal

    @param unexpected What this assertion is expected not to be
  */
  void not_equal(const T& unexpected) throw(){
    if (result == unexpected){
      std::stringstream ss;
      ss << "'" << result << "' is equal to '" << unexpected << "'";
      fail(ss.str());
    }
  }

  /** Assert this value is NULL */
  void is_null(){
    if (result != 0){
      std::stringstream ss;
      ss << "'" << result << "' is not NULL";
      fail(ss.str());
    }
  }

  /** Assert this value is not NULL */
  void not_null(){
    if (result == 0){
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
  void nearly_equals(const T& expected, const T& delta) throw(){
    if (fabs(expected - result) > delta){
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
  void greater_than(const T& limit) throw(){
    if (result <= limit){
      std::stringstream ss;
      ss << "'" << result << "' is not greater than '" << limit << "'";
      fail(ss.str());
    }
  }

  /**
    Check that the result is greater than or equal to some expected value

    @param limit The number the result must be above or equal to
  */
  void greater_than_or_equal(const T& limit) throw(){
    if (result < limit){
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
  void less_than(const T& limit) throw(){
    if (result >= limit){
      std::stringstream ss;
      ss << "'" << result << "' is not less than '" << limit << "'";
      fail(ss.str());
    }
  }

  /**
    Check that the result is less than or equal to some expected value

    @param limit The number the result must be below or equal to
  */
  void less_than_or_equal(const T& limit) throw(){
    if (result > limit){
      std::stringstream ss;
      ss << "'" << result << "' is not less than or equal to '" << limit << "'";
      fail(ss.str());
    }
  }

  /**
    Check that the value can be evaluated to the boolean value 'true'
  */
  void is_true() throw(){
    if (!result){
      fail("Expected to be true, but is false");
    }
  }

  /**
    Check that the value can be evaluated to the boolean value 'false'
  */
  void is_false() throw(){
    if (result){
      fail("Expected to be false, but is true");
    }
  }

protected:
  const T result;
};

} /* Namespace */

#endif /* TEST_H */
