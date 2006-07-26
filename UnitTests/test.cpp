#include "test.h"
#include "test_registry.h"
#include "test_result.h"
#include "output_handler.h"

namespace UnitTests {

Test::Test(const std::string& _name, const std::string& _suite_name,
  bool _has_fixture) throw():
  failed(false), name(_name), suite_name(_suite_name),
  has_fixture(_has_fixture){

  TestRegistry::add(this);
}

void Test::run() throw() {
  try {
    set_up();
    _run();
    tear_down();
  }

  catch (const std::exception& e){
    fail(std::string("Unhandled exception: ") + e.what());
  }

  catch (...){
    fail("Unhandled, unknown exception");
  }

  pass();
}

void Test::run_no_exceptions() throw(){
  set_up();
  _run();
  tear_down();

  pass();
}

void Test::pass() const throw() {
  if (!failed){
    TestResult::pass(this);
  }
}

void Test::fail(const std::string& message) throw() {
  if (!failed){
    TestResult::fail(this, message);
    failed = true;
  }
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
