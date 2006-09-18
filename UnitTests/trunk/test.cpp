#include <list>
#include "test.h"
#include "suite.h"
#include "output_handlers/default_output_handler.h"
#include "failure_exception.h"
#include "protectors/exception_protector.h"

namespace UnitTests {

Test::Test(
  const std::string& _name,
  Suite* _suite,
  const std::string& _file_name) throw ():

  name(_name),
  suite(_suite),
  file_name(_file_name) {

  _suite->add_test(this);
}

Test::~Test() {}

void Test::run() {
  set_up();
  _run();
  tear_down();
}

} // namespace

using namespace UnitTests;

int main(int argc, char** argv) {
  // Allow exception catching to be toggled on or off at runtime
  bool catch_exceptions = true;
  if (argc > 1) {
    if (strcmp(argv[1], "--no-exceptions") == 0) {
      catch_exceptions = false;
    }
  }

  ExceptionProtector exception_protector;

  if (catch_exceptions) {
    Protector::add(&exception_protector);
  }

  // Where output will be directed to
  DefaultOutputHandler output;
  std::list<Suite*> suites = Suite::all_suites();
  std::list<Suite*>::const_iterator suite;
  for (suite = suites.begin(); suite != suites.end(); suite++) {

    std::list<Test*> tests = (*suite)->get_tests();
    std::list<Test*>::const_iterator test;
    for (test = tests.begin(); test != tests.end(); test++) {
      try {
        output.begin(*test);
        Protector::guard(*test);
        output.pass(*test);
      }

      catch (const FailureException& e) {
        output.fail(*test, e); 
      }

      catch (const ErrorException& e) {
        output.error(*test, e); 
      }
    }
  }

  return 0;
}
