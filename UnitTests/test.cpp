#include "test.h"
#include "test_registry.h"
#include "output_handler.h"
#include "failure_exception.h"

namespace UnitTests {

Test::Test(
  const std::string& name,
  const std::string& suite_name,
  const unsigned int line_number) throw ():

  test_name(name),
  test_suite_name(suite_name),
  test_line_number(line_number){

  TestRegistry::add(this);
}

void Test::run() throw (FailureException) {
  try {
    set_up();
    _run();
    tear_down();
  }

  catch (const std::exception& e){
    throw FailureException(std::string("Unhandled exception: ") + e.what());
  }

  catch (const FailureException&){
    throw;
  }

  catch (...){
    throw FailureException("Unhandled, unknown exception");
  }
}

void Test::run_no_exceptions() {
  set_up();
  _run();
  tear_down();
}

std::string Test::get_string() const throw (){
  std::stringstream ss;
  ss << test_suite_name << "::" << test_name << " (line "
    << test_line_number << ")";
  return ss.str();
}

} // namespace

using namespace UnitTests;

int main(int argc, char** argv){
  DefaultOutputHandler* handler = new DefaultOutputHandler;
  bool catch_exceptions = true;
  if (argc > 1){
    if (std::string(argv[1]) == "--no-exceptions"){
      catch_exceptions = false;
    }
  }

  TestRegistry::run_all(handler, catch_exceptions);
  delete handler;

  return 0;
}
