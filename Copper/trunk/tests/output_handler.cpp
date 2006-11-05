/* output_handler.cpp -- Outputs tests results to stdout and stderr
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <time.h>
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
  std::time_t start_time;
  time(&start_time);

  // Run all tests
  run_tests(Copper::Test::all());

  // Calculate running time
  std::time_t now;
  time(&now);

  // Print statistics
  printf(
    "%u tests passed\n"
    "%u tests failed\n"
    "%u errors\n", num_passed, num_failed, num_errors);

  // Print running time
  printf("Completed in %g seconds\n", difftime(now, start_time));

  return num_failed + num_errors;
}
