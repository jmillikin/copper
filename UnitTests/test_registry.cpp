#include "test_registry.h"
#include "test.h"
#include "output_handler.h"
#include "protector.h"
#include "protectors/exception_protector.h"

namespace UnitTests {

class TestNode {
public:
  TestNode(Test* _test):
    test(_test), next(0){

    static unsigned int next_id = 0;
    id = next_id;
    ++next_id;
  }
  Test* test;
  unsigned int id;

  TestNode* next;
};

std::list<Test*> TestRegistry::tests;

void TestRegistry::add(Test* test) throw () {
  tests.push_back(test);
}

void TestRegistry::run_all(OutputHandler* output, bool catch_exceptions) {
  ExceptionProtector exception_protector;

  if (catch_exceptions) {
    Protector::add(&exception_protector);
  }

  std::list<Test*>::iterator test;
  for (test = tests.begin(); test != tests.end(); test++) {
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

} /* namespace */
