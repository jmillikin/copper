/* suite.cpp -- Groups tests into logical groups
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper/suite.hpp>
#include "export.hpp"

namespace Copper {

List<Suite>& suites() throw () {
  static List<Suite> _suites;
  return _suites;
}

EXPORT Suite::Suite(const String& _name) throw ():
  name(_name) {

  suites().append(this);
}

EXPORT Suite::~Suite() throw () {}

void Suite::add_test(Test* test) throw () {
  tests.append(test);
}

EXPORT List<Test> Suite::get_tests() const throw () {
  return tests;
}

EXPORT List<Suite> Suite::all_suites() throw () {
  return suites();
}

} // namespace
