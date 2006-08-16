#ifndef ASSERTION_H
#define ASSERTION_H

/* For fabs() */
#include <cmath>

/* For formatting error strings */
#include <sstream>

// Disable warnings about throw specifications in VS 2003
#pragma warning(disable: 4290)

#include "failure_exception.h"

namespace UnitTests {

class Test;

template <class T>
class Assertion {
public:
  /**
    Create an assertion

    @param value The value to assert against
    @param test The test this assertion was created in
  */
  Assertion(const T& value, Test* _test) throw ():
    test(_test), result(value){}

  /**
    Assert the two values are equal

    @param expected The expected value of this assertion
  */
  void equals(const T& expected) const throw (FailureException) {
    if (result != expected){
      std::stringstream ss;
      ss << "Unequal values: expected '" << expected << "', got '" << result << "'";
      throw FailureException(ss.str());
    }
  }

  /**
    Assert that two values are not equal

    @param unexpected What this assertion is expected not to be
  */
  void not_equals(const T& unexpected) const throw (FailureException) {
    if (result == unexpected){
      std::stringstream ss;
      ss << "'" << result << "' is equal to '" << unexpected << "'";
      throw FailureException(ss.str());
    }
  }

  /** Assert this value is NULL */
  void is_null() const throw (FailureException) {
    if (result != 0){
      std::stringstream ss;
      ss << "'" << result << "' is not NULL";
      throw FailureException(ss.str());
    }
  }

  /** Assert this value is not NULL */
  void not_null() const throw (FailureException) {
    if (result == 0){
      std::stringstream ss;
      ss << "'" << result << "' is NULL";
      throw FailureException(ss.str());
    }
  }

  /**
    Check that the two values are nearly equal within a certain delta

    @param expected The expected floating-point number
    @param delta The allowable difference between the expected and actual
    values
  */
  void nearly_equals(const T& expected, const T& delta)
    const throw (FailureException) {

    if (fabs(expected - result) > delta){
      std::stringstream ss;
      ss << "Result '" << result << "' is not within '" << delta << "' of '"
        << expected << "'";
      throw FailureException(ss.str());
    }
  }

  /**
    Check that the result is greater than some expected value

    @param limit The number the result must be above
  */
  void greater_than(const T& limit) const throw (FailureException) {
    if (result <= limit){
      std::stringstream ss;
      ss << "'" << result << "' is not greater than '" << limit << "'";
      throw FailureException(ss.str());
    }
  }

  /**
    Check that the result is greater than or equal to some expected value

    @param limit The number the result must be above or equal to
  */
  void greater_than_or_equal(const T& limit) const throw (FailureException) {
    if (result < limit){
      std::stringstream ss;
      ss << "'" << result << "' is not greater than or equal to '" << limit
        << "'";
      throw FailureException(ss.str());
    }
  }

  /**
    Check that the result is less than some expected value

    @param limit The number the result must be below
  */
  void less_than(const T& limit) const throw (FailureException) {
    if (result >= limit){
      std::stringstream ss;
      ss << "'" << result << "' is not less than '" << limit << "'";
      throw FailureException(ss.str());
    }
  }

  /**
    Check that the result is less than or equal to some expected value

    @param limit The number the result must be below or equal to
  */
  void less_than_or_equal(const T& limit) const throw (FailureException) {
    if (result > limit){
      std::stringstream ss;
      ss << "'" << result << "' is not less than or equal to '" << limit << "'";
      throw FailureException(ss.str());
    }
  }

  /**
    Check that the result is between two numbers. This will fail if the result
    equals one of the numbers - for an inclusive test, use @between_inclusive

    @param lower The lower bound of the range
    @param upper The upper bound of the range
  */
  void between(const T& lower, const T& upper) const throw (FailureException) {
    if (result <= lower || result >= upper){
      std::stringstream ss;
      ss << "'" << result << "' is not between '" << lower << "' and '"
        << upper << "'";
      throw FailureException(ss.str());
    }
  }

  /**
    Check that the result is between two numbers. This test is inclusive, and
    will pass if the result equals one of the boundary values

    @param lower The lower bound of the range
    @param upper The upper bound of the range
  */
  void between_inclusive(const T& lower, const T& upper)
    const throw (FailureException) {

    if (result < lower || result > upper){
      std::stringstream ss;
      ss << "'" << result << "' is not between or equal to '"
        << lower << "' and '" << upper << "'";
      throw FailureException(ss.str());
    }
  }

  /**
    Check that the value can be evaluated to the boolean value 'true'
  */
  void is_true() const throw (FailureException) {
    if (!result){
      throw FailureException("Expected to be true, but is false");
    }
  }

  /**
    Check that the value can be evaluated to the boolean value 'false'
  */
  void is_false() const throw (FailureException) {
    if (result){
      throw FailureException("Expected to be false, but is true");
    }
  }

protected:
  Test* test;
  const T result;
};

} /* Namespace */

#endif /* TEST_H */
