#ifndef DEFAULT_OUTPUT_HANDLER_H
#define DEFAULT_OUTPUT_HANDLER_H

#include "../output_handler.h"

namespace UnitTests {

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

  /** Run every test available */
  void run();

protected:
  /** The number of tests that have passed */
  unsigned int num_passed;

  /** The number of failed tests */
  unsigned int num_failed;

  /** The number of tests that had errors */
  unsigned int num_errors;

  /** How long tests took to complete */
  double running_time;
};

} /* namespace */

#endif /* OUTPUT_HANDLER_H */
