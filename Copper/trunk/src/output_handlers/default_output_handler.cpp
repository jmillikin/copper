/* default_output_handler.cpp -- Outputs to stdout and stderr
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <sys/time.h>
#include <cstdio>
#include "default_output_handler.hpp"
#include "../export.hpp"

namespace Copper {

EXPORT DefaultOutputHandler::DefaultOutputHandler(int& argc, char**& argv)
  throw ():
  OutputHandler(argc, argv),
  num_passed(0),
  num_failed(0),
  num_errors(0) {}

EXPORT DefaultOutputHandler::~DefaultOutputHandler() throw () {}

void DefaultOutputHandler::begin(const Test*) throw () {}

void DefaultOutputHandler::pass(const Test*) throw () {
  ++num_passed;
}

void DefaultOutputHandler::fail(const Test* test,
  const Assertion* assertion) throw () {

  ++num_failed;

  fprintf(stderr,
    "FAILURE in %s:%u:\n"
    "%s - %s:\n"
    "  %s\n"
    "  %s\n\n",
    test->file_name, assertion->line(),
    pretty_name(test->suite->name).c_str(), pretty_name(test->name).c_str(),
    assertion->text(), assertion->failure_message());
}

void DefaultOutputHandler::error(const Test* test, const Error* error)
  throw () {

  ++num_errors;

  fprintf(stderr,
    "ERROR in %s:\n"
    "%s - %s:\n"
    "  %s\n\n",
    test->file_name,
    pretty_name(test->suite->name).c_str(), pretty_name(test->name).c_str(),
    error->message);
}

EXPORT int DefaultOutputHandler::run() {
  // Reset statistics
  num_passed = 0;
  num_failed = 0;
  num_errors = 0;

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
  double running_time = now.tv_sec - start_time.tv_sec;

  // 1,000,000 microseconds in a second
  running_time += static_cast<double>( now.tv_usec - start_time.tv_usec)
    / 1000000.0;

  // Print statistics
  printf(
    "%u tests passed\n"
    "%u tests failed\n"
    "%u errors\n", num_passed, num_failed, num_errors);

  // Print running time
  printf("Completed in %f seconds\n", running_time);

  return num_failed + num_errors;
}

} /* namespace */
