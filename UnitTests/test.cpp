#include "test.h"
#include "output_handler.h"
#include "failure_exception.h"
#include "protectors/exception_protector.h"
#include <list>

namespace UnitTests {

std::list<Test*>* tests = 0;

Test::Test(
  const std::string& _name,
  const std::string& _suite_name,
  const std::string& _file_name) throw ():
  name(_name),
  suite_name(_suite_name),
  file_name(_file_name) {

  static std::list<Test*> _tests;
  if (!tests) {
    tests = &_tests;
  }
  tests->push_back(this);
}

Test::~Test() {}

void Test::run() {
  set_up();
  _run();
  tear_down();
}

void Test::run_all(OutputHandler* output, bool catch_exceptions) {
  if (!tests) {
    return;
  }

  ExceptionProtector exception_protector;

  if (catch_exceptions) {
    Protector::add(&exception_protector);
  }

  std::list<Test*>::iterator test;
  for (test = tests->begin(); test != tests->end(); test++) {
    try {
      output->begin(*test);
      Protector::guard(*test);
      output->pass(*test);
    }   

    catch (const FailureException& e) {
      output->fail(*test, e); 
    }   

    catch (const ErrorException& e) {
      output->error(*test, e); 
    }   
  }
}

} // namespace

using namespace UnitTests;

int main(int argc, char** argv) {
  DefaultOutputHandler handler;
  bool catch_exceptions = true;
  if (argc > 1) {
    if (strcmp(argv[1], "--no-exceptions") == 0) {
      catch_exceptions = false;
    }
  }

  Test::run_all(&handler, catch_exceptions);

  return 0;
}
