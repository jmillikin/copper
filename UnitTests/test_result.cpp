#include "test_result.h"
#include "output_handler.h"
#include "test.h"

namespace UnitTests {

OutputHandler* TestResult::handler(0);

void TestResult::pass(const Test* test) throw() {
  if (handler){
    handler->pass(test);
  }
}

void TestResult::fail(const Test* test, const std::string& message) throw() {
  if (handler){
    handler->fail(test, message);
  }
}

void TestResult::set_output_handler(OutputHandler* new_handler) throw() {
  handler = new_handler;
}

} /* namespace */
