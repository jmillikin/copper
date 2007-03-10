/* suite.hpp -- Groups tests into logical groups
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_SUITE_HPP
#define COPPER_SUITE_HPP

#include <copper/util/list.hpp>
#include <copper/util/string.hpp>

namespace Copper {

class Test;

class Suite {
public:
  /**
    Default constructor

    @param name The name of the test suite
  */
  Suite(const String& name) throw ();

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
  List<Test> get_tests() const throw ();

  /** Get a list of all test suites */
  static List<Suite> all_suites() throw ();

  /** This suite's name */
  const String name;

protected:
  /** All tests in this suite, in no particular order */
  List<Test> tests;
};

} // namespace

#endif /* COPPER_SUITE_HPP */
