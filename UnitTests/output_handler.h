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

/**
  This is a default implementation of an OutputHandler. It will output failures
  to the standard error stream
*/
class DefaultOutputHandler : public OutputHandler {
public:
  /** Default constructor */
  DefaultOutputHandler() throw ();

  /** Default destructor */
  ~DefaultOutputHandler() throw ();

  /** Does nothing */
  void begin(const Test* test) throw ();

  /**
    Outputs nothing, but keeps track of how many tests passed

    @param test The test that passed
  */
  void pass(const Test* test) throw ();

  /**
    Outputs failures to the standard error stream. Also keeps track of how
    many tests failed

    @param test The test that failed
    @param failure The failure that was thrown
  */
  void fail(const Test* test, const FailureException& failure)
    throw ();

  /**
    Outputs errors to the standard error stream. Also keeps track of how
    many tests errored out

    @param test The test that failed
    @param error The error that was thrown
  */
  void error(const Test* test, const ErrorException& error) throw ();

protected:
  /** The number of tests that have passed */
  unsigned int num_passed;

  /** The number of failed tests */
  unsigned int num_failed;

  /** The number of tests that had errors */
  unsigned int num_errors;
};

} /* namespace */

#endif /* OUTPUT_HANDLER_H */
