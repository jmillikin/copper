#include "test_registry.h"
#include "test.h"
#include "output_handler.h"

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

TestNode* TestRegistry::first(0);

TestRegistry::TestRegistry() throw() {}

TestRegistry::~TestRegistry() throw () {}

void TestRegistry::add(Test* test) throw () {
  TestNode* node = new TestNode(test);

  if (!first){
    first = node;
  }

  else {
    TestNode* parent = first;
    while (parent->next){
      parent = parent->next;
    }

    parent->next = node;
  }
}

void TestRegistry::run_all(OutputHandler* output, bool catch_exceptions)
  throw () {

  TestNode* node = first;

  while (node){
    try {
      if (catch_exceptions){
        node->test->run();
      }

      else {
        node->test->run_no_exceptions();
      }

      output->pass(node->test);
    }

    catch (const FailureException& e){
      output->fail(node->test, e.get_message());
    }
    node = node->next;
  }
}

} /* namespace */
