#include "test.h"
#include "test_registry.h"
#include "test_result.h"
#include "output_handler.h"

namespace UnitTests {

Test::Test(const std::string& _name, const std::string& _suite_name) throw():
  name(_name), suite_name(_suite_name){

  TestRegistry::add(this);
}

void Test::run() const throw() {
  try {
    _run();
  }

  catch (const std::exception& e){
    fail(std::string("Unhandled exception: ") + e.what());
  }

  catch (...){
    fail("Unhandled, unknown exception");
  }
}

void Test::run_no_exceptions() const throw(){
  _run();
}

void Test::pass() const throw() {
  TestResult::pass(this);
}

void Test::fail(const std::string& message) const throw() {
  TestResult::fail(this, message);
}

} // namespace

using namespace UnitTests;

int main(){
  DefaultOutputHandler* handler = new DefaultOutputHandler;
  TestResult::set_output_handler(handler);
  TestRegistry::run_all();
  delete handler;

  return 0;
}
