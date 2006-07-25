#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include <string>

namespace UnitTests {

class Test;

/**
  This class must be subclassed to provide different output formats
*/
class OutputHandler {
public:
  /** Empty constructor */
  OutputHandler(){}

  /** Empty destructor */
  virtual ~OutputHandler(){}

  /**
    This function is called whenever a test passes

    @param test The test that passed
  */
  virtual void pass(const Test* test) throw() = 0;

  /**
    This function is called whenever a test fails

    @param test The test that failed
    @param message The message from the test, if available
  */
  virtual void fail(const Test* test, const std::string& message) throw()= 0;
};

/**
  This is a default implementation of an OutputHandler. It will output failures
  to the standard error stream
*/
class DefaultOutputHandler : public OutputHandler {
public:
  /** Empty constructor */
  DefaultOutputHandler(){}

  /** Empty destructor */
  virtual ~DefaultOutputHandler(){}

  /** Does nothing */
  virtual void pass(const Test* test) throw();

  /**
    Outputs to the standard error stream in this form

    Test 'suite_name::test_name' failed: message

    @param test The test that failed
    @param message The message from the test, if available
  */
  virtual void fail(const Test* test, const std::string& message) throw();
};

} /* namespace */

#endif /* OUTPUT_HANDLER_H */
