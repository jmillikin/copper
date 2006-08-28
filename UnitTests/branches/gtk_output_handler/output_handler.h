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
    Outputs errors to the standard error stream. Also keeps track of how
    many tests errored out

    @param test The test that failed
    @param error The error that was thrown
  */
  virtual void error(const Test* test, const ErrorException& error)
    throw () = 0;
};

} /* namespace */

#endif /* OUTPUT_HANDLER_H */
