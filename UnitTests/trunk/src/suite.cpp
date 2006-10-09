/* suite.cpp -- Groups tests into logical groups
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "suite.hpp"
#include "protectors/exception_protector.hpp"
#include "export.hpp"
#include <list>

namespace UnitTests {

std::list<Suite*>* suites() throw () {
  static std::list<Suite*> _suites;
  return &_suites;
}

EXPORT Suite::Suite(const char* _name) throw ():
  name(_name) {

  suites()->push_back(this);
}

EXPORT Suite::~Suite() throw () {}

void Suite::add_test(Test* test) throw () {
  tests.push_back(test);
}

std::list<Test*> Suite::get_tests() const throw () {
  return tests;
}

std::list<Suite*> Suite::all_suites() throw () {
  return *suites();
}

} // namespace
