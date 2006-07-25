#ifndef TEST_RESULT_H
#define TEST_RESULT_H

#include <string>

namespace UnitTests {

class OutputHandler;
class Test;

class TestResult {
public:
  static void pass(const Test* test) throw();
  static void fail(const Test* test, const std::string& message) throw();
  static void set_output_handler(OutputHandler* handler) throw();

protected:
  static OutputHandler* handler;
};

} /* namespace */

#endif /* TEST_RESULT_H */
