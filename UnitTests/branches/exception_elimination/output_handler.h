/* output_handler.h -- Base class for all output handlers
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

namespace UnitTests {

class Test;
class Assertion;
class ErrorException;

/**
  This class must be subclassed to provide different output formats
*/
class OutputHandler {
public:
  /** Default constructor */
  OutputHandler(int& argc, char**& argv);

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
    @param assertion The assertion that failed
  */
  virtual void fail(const Test* test, const Assertion& assertion)
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