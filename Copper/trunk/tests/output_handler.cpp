/* output_handler.cpp -- Outputs tests results to stdout and stderr
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <sys/time.h>
#include <cstdio>
#include <cstring>
#include <copper/protectors/exception_protector.hpp>
#include "output_handler.hpp"

OutputHandler::OutputHandler(int& argc, char**& argv)
  throw ():
  Copper::OutputHandler(argc, argv),
  num_passed(0),
  num_failed(0),
  num_errors(0) {

  // Allow exception catching to be toggled on or off at runtime
  bool catch_exceptions = true;
  for (int ii = 1; ii < argc; ii++) {
    if (std::strcmp(argv[ii], "--no-exceptions") == 0) {
      catch_exceptions = false;
      break;
    }   
  }

  if (catch_exceptions) {
    static Copper::ExceptionProtector exception_protector;
    Copper::Protector::add(&exception_protector);
  }
}

OutputHandler::~OutputHandler() throw () {}

void OutputHandler::begin(const Copper::Test*) throw () {}

void OutputHandler::pass(const Copper::Test*) throw () {
  ++num_passed;
}

void OutputHandler::fail(const Copper::Test* test,
  const Copper::Assertion* assertion) throw () {

  ++num_failed;

  Copper::String suite_name = pretty_name(test->suite->name);
  Copper::String test_name = pretty_name(test->name);

  std::fprintf(stderr,
    "FAILURE in %s:%u:\n"
    "%s - %s:\n"
    "  %s\n"
    "  %s\n\n",
    test->file_name.c_str(), assertion->line(),
    suite_name.c_str(), test_name.c_str(),
    assertion->text().c_str(),
    assertion->failure_message().c_str());
}

void OutputHandler::error(
  const Copper::Test* test,
  const Copper::Error* error) throw () {

  ++num_errors;

  Copper::String suite_name = pretty_name(test->suite->name);
  Copper::String test_name = pretty_name(test->name);

  std::fprintf(stderr,
    "ERROR in %s:\n"
    "%s - %s:\n"
    "  %s\n\n",
    test->file_name.c_str(),
    suite_name.c_str(), test_name.c_str(),
    error->message.c_str());
}

int OutputHandler::run() {
  // Reset statistics
  num_passed = 0;
  num_failed = 0;
  num_errors = 0;

  // Store when the tests started
  timeval start_time;
  gettimeofday(&start_time, 0);

  // Run all tests
  run_tests(Copper::Test::all());

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
