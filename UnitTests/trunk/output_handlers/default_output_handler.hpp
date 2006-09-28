/* default_output_handler.hpp -- Outputs to stdout and stderr
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef DEFAULT_OUTPUT_HANDLER_HPP
#define DEFAULT_OUTPUT_HANDLER_HPP

#include "../output_handler.hpp"

namespace UnitTests {

/**
  This is a default implementation of an OutputHandler. It will output failures
  to the standard error stream
*/
class DefaultOutputHandler : public OutputHandler {
public:
  /** Default constructor */
  DefaultOutputHandler(int& argc, char**& argv) throw ();

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
    @param assetion The assertion that caused the test to fail
  */
  void fail(const Test* test, const Assertion* assertion) throw ();

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

#endif /* OUTPUT_HANDLER_HPP */
