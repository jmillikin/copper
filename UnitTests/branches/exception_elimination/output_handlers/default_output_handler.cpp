/* default_output_handler.cpp -- Outputs to stdout and stderr
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <sys/time.h>
#include "default_output_handler.h"
#include "../test.h"
#include "../error_exception.h"

namespace UnitTests {

DefaultOutputHandler::DefaultOutputHandler(int& argc, char**& argv)
  throw ():
  OutputHandler(argc, argv),
  num_passed(0),
  num_failed(0),
  num_errors(0) {}

DefaultOutputHandler::~DefaultOutputHandler() throw () {
  // Print statistics
  printf(
    "%u tests passed\n"
    "%u tests failed\n"
    "%u errors\n", num_passed, num_failed, num_errors);

  // Print running time
  printf("Completed in %lf seconds\n", running_time);
}

void DefaultOutputHandler::begin(const Test*) throw () {}

void DefaultOutputHandler::pass(const Test*) throw () {
  ++num_passed;
}

void DefaultOutputHandler::fail(const Test* test,
  const FailureException& failure) throw () {

  ++num_failed;

  fprintf(stderr,
    "FAILURE in %s:%u:\n"
    "%s::%s:\n"
    "  %s\n"
    "  %s\n\n",
    test->file_name, failure.line,
    test->suite->name, test->name,
    failure.assertion, failure.message);
}

void DefaultOutputHandler::error(const Test* test,
  const ErrorException& error) throw () {

  ++num_errors;

  fprintf(stderr,
    "ERROR in %s:\n"
    "%s::%s:\n"
    "  %s\n\n",
    test->file_name,
    test->suite->name, test->name,
    error.message);
}

void DefaultOutputHandler::run() {
  // Store when the tests started
  timeval start_time;
  gettimeofday(&start_time, 0);

  std::list<Suite*> suites = Suite::all_suites();
  std::list<Suite*>::const_iterator suite;
  for (suite = suites.begin(); suite != suites.end(); suite++) {

    std::list<Test*> tests = (*suite)->get_tests();
    std::list<Test*>::const_iterator test;
    for (test = tests.begin(); test != tests.end(); test++) {
      run_test(*test);
    }
  }

  // Calculate running time
  timeval now;
  gettimeofday(&now, 0);
  running_time = now.tv_sec - start_time.tv_sec;
  
  running_time += static_cast<double>(now.tv_usec - start_time.tv_usec) /
    1000000.0; // 1,000,000 microseconds in a second
}

} /* namespace */
