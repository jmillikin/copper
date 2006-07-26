#ifndef TEST_REGISTRY_H
#define TEST_REGISTRY_H

namespace UnitTests {

class Test;

class TestNode;

/**
  A simple registry of all tests, which will run every test when prompted
*/
class TestRegistry {
public:
  TestRegistry() throw();
  static void add(Test* test) throw();
  static void run_all() throw();

protected:
  static TestNode* first;
};

} /* namespace */

#endif /* TEST_REGISTRY_H */
