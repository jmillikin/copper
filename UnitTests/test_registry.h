#ifndef TEST_REGISTRY_H
#define TEST_REGISTRY_H

namespace UnitTests {

class Test;
class TestNode;
class OutputHandler;

/**
  A simple registry of all tests, which will run every test when prompted
*/
class TestRegistry {
public:
  /** Create a new test registry, which will output to the given */
  TestRegistry() throw ();

  /** Default destructor */
  ~TestRegistry() throw ();

  /**
    Add a new test to the test list. The test list is shared among all
    test registries

    @param test The test to add
  */
  static void add(Test* test) throw ();

  /**
    Run all tests, sending results to the given output handler

    @param output The output handler to output to
    @param catch_exceptions Whether to catch unknown exceptions encountered
    during testing. If this is set to false, the testing program will terminate
    when it cannot deal with an exception
  */
  static void run_all(OutputHandler* output, bool catch_exceptions = true);

protected:
  static TestNode* first;
};

} /* namespace */

#endif /* TEST_REGISTRY_H */
