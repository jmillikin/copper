#include "suite.h"
#include "failure_exception.h"
#include "protectors/exception_protector.h"
#include <list>

namespace UnitTests {

Suite::Suite(const std::string& _name) throw ():
  name(_name) {}

Suite::~Suite() throw () {}

void Suite::add_test(Test* test) throw () {
  tests.push_back(test);
}

std::list<Test*> Suite::get_tests() const throw () {
  return tests;
}

std::string Suite::get_name() const throw () {
  return name;
}

} // namespace
