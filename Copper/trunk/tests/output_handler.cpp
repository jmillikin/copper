/* output_handler.cpp -- Outputs tests results to stdout and stderr
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <sys/time.h>
#include <cstdio>
#include "output_handler.hpp"

OutputHandler::OutputHandler(int& argc, char**& argv)
  throw ():
  Copper::OutputHandler(argc, argv),
  num_passed(0),
  num_failed(0),
  num_errors(0) {}

OutputHandler::~OutputHandler() throw () {}

void OutputHandler::begin(const Copper::Test*) throw () {}

void OutputHandler::pass(const Copper::Test*) throw () {
  ++num_passed;
}

void OutputHandler::fail(const Copper::Test* test,
  const Copper::Assertion* assertion) throw () {

  ++num_failed;

  char* suite_name = pretty_name(test->suite->name);
  char* test_name = pretty_name(test->name);

  fprintf(stderr,
    "FAILURE in %s:%u:\n"
    "%s - %s:\n"
    "  %s\n"
    "  %s\n\n",
    test->file_name, assertion->line(),
    suite_name, test_name,
    assertion->text(), assertion->failure_message());

  free(suite_name);
  free(test_name);
}

void OutputHandler::error(
  const Copper::Test* test,
  const Copper::Error* error) throw () {

  ++num_errors;

  char* suite_name = pretty_name(test->suite->name);
  char* test_name = pretty_name(test->name);

  fprintf(stderr,
    "ERROR in %s:\n"
    "%s - %s:\n"
    "  %s\n\n",
    test->file_name, suite_name, test_name, error->message);

  free(suite_name);
  free(test_name);
}

int OutputHandler::run() {
  // Reset statistics
  num_passed = 0;
  num_failed = 0;
  num_errors = 0;

  // Store when the tests started
  timeval start_time;
  gettimeofday(&start_time, 0);

  std::list<Copper::Suite*> suites = Copper::Suite::all_suites();
  std::list<Copper::Suite*>::const_iterator suite;
  for (suite = suites.begin(); suite != suites.end(); suite++) {

    std::list<Copper::Test*> tests = (*suite)->get_tests();
    std::list<Copper::Test*>::const_iterator test;
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
