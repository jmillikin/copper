/* suite.hpp -- Groups tests into logical groups
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef SUITE_HPP
#define SUITE_HPP

#include <list>

namespace Copper {

class Test;

class Suite {
public:
  /**
    Default constructor

    @param name The name of the test suite
  */
  Suite(const char* name) throw ();

  /** Default destructor */
  ~Suite() throw ();

  /**
    Add a test to this suite. Should never be used except in the constructor
    for the Test class
  */
  void add_test(Test* test) throw ();

  /**
    Get the list of tests in this suite

    @return All tests in this suite, in no particular order
  */
  std::list<Test*> get_tests() const throw ();

  /** Get a list of all test suites */
  static std::list<Suite*> all_suites() throw ();

  /** This suite's name */
  const char* name;

protected:
  /** All tests in this suite, in no particular order */
  std::list<Test*> tests;
};

} // namespace

#endif /* SUITE_HPP */
