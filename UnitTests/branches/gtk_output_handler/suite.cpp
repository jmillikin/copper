#include "suite.h"
#include "failure_exception.h"
#include "protectors/exception_protector.h"
#include <list>

namespace UnitTests {

std::list<Suite*>* suites() throw () {
  static std::list<Suite*> _suites;
  return &_suites;
}

Suite::Suite(const std::string& _name) throw ():
  name(_name) {

  suites()->push_back(this);
}

Suite::~Suite() throw () {}

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
