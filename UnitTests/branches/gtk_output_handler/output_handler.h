#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

namespace UnitTests {

class Test;
class FailureException;
class ErrorException;

/**
  This class must be subclassed to provide different output formats
*/
class OutputHandler {
public:
  /** Default constructor */
  OutputHandler();

  /** Default destructor */
  virtual ~OutputHandler();

  /**
    This function is called whenever a test is begun

    @param test The test that is about to run
  */
  virtual void begin(const Test* test) throw () = 0;

  /**
    This function is called whenever a test passes

    @param test The test that passed
  */
  virtual void pass(const Test* test) throw () = 0;

  /**
    This function is called whenever a test fails

    @param test The test that failed
    @param failure The failure that was thrown
  */
  virtual void fail(const Test* test, const FailureException& failure)
    throw ()= 0;

  /**
    This function is called whenever a test encounters an error while running

    @param test The test that failed
    @param error The error that was thrown
  */
  virtual void error(const Test* test, const ErrorException& error)
    throw () = 0;

  /**
    Run this output handler. The simplest implementations will run every test,
    the more complex ones may allow selection of which tests to run
  */
  virtual void run() = 0;

protected:
  /**
    Run a single test. This function automatically manages Protectors and
    exception handling

    @param test The test to run
  */
  void run_test(Test* test);
};

} /* namespace */

#endif /* OUTPUT_HANDLER_H */
