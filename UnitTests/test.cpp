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
#ifdef CATCH_EXCEPTIONS
  try {
#endif
    _run();
#ifdef CATCH_EXCEPTIONS
  } catch (...){
    fail("Unhandled exception");
  }
#endif
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
  TestResult::set_output_handler(new DefaultOutputHandler);
  TestRegistry::run_all();

  return 0;
}
