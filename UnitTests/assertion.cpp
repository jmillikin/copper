#include "assertion.h"
#include "test.h"

namespace UnitTests {

BaseAssertion::BaseAssertion(Test* _test) throw(): test(_test){}

void BaseAssertion::fail(const std::string& message) throw(){
  test->fail(message);
}

} /* namespace */
