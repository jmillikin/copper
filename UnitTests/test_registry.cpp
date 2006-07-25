#include "test_registry.h"
#include "test.h"

namespace UnitTests {

class TestNode {
public:
  TestNode(const Test* _test):
    test(_test), next(0){

    static unsigned int next_id = 0;
    id = next_id;
    ++next_id;
  }
  const Test* test;
  unsigned int id;

  TestNode* next;
};

TestRegistry::TestRegistry() throw() {}

TestNode* TestRegistry::first(0);

void TestRegistry::add(const Test* test) throw() {
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

void TestRegistry::run_all() throw() {
  TestNode* node = first;

  while (node){
    node->test->run();
    node = node->next;
  }
}

} /* namespace */
