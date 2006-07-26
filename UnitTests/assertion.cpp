#include "assertion.h"
#include "test.h"

namespace UnitTests {

BaseAssertion::BaseAssertion(const Test* _test) throw(): test(_test){}

void BaseAssertion::pass() const throw(){
  test->pass();
}

void BaseAssertion::fail(const std::string& message) const throw(){
  test->fail(message);
}

} /* namespace */
