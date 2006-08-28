#ifndef SUITE_H
#define SUITE_H

#include <list>
#include <string>

namespace UnitTests {

class Test;

class Suite {
public:
  /**
    Default constructor

    @param name The name of the test suite
  */
  Suite(const std::string& name) throw ();

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

  /**
    Get this suite's name

    @return The name of this test suite
  */
  std::string get_name() const throw ();

protected:
  /** All tests in this suite, in no particular order */
  std::list<Test*> tests;

  /** The name of this test suite */
  std::string name;
};

} // namespace

#endif /* SUITE_H */
