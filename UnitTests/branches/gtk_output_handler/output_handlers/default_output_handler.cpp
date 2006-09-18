#include <iostream>
#include "default_output_handler.h"
#include "../test.h"
#include "../error_exception.h"

namespace UnitTests {

DefaultOutputHandler::DefaultOutputHandler() throw ():
  OutputHandler(),
  num_passed(0),
  num_failed(0),
  num_errors(0) {}

DefaultOutputHandler::~DefaultOutputHandler() throw () {
  // Print statistics
  std::cout
    << num_passed << " tests passed\n"
    << num_failed << " tests failed\n"
    << num_errors << " errors\n";
}

void DefaultOutputHandler::begin(const Test*) throw () {}

void DefaultOutputHandler::pass(const Test*) throw () {
  ++num_passed;
}

void DefaultOutputHandler::fail(const Test* test,
  const FailureException& failure) throw () {

  ++num_failed;

  std::cerr
    << "FAILURE in " << test->file_name << ":" << failure.line << ":\n"
    << test->suite->name << "::" << test->name << ":\n"
    << "  " << failure.message << "\n\n";
}

void DefaultOutputHandler::error(const Test* test,
  const ErrorException& error) throw () {

  ++num_errors;

  std::cerr
    << "ERROR in " << test->file_name << ":\n"
    << test->suite->name << "::" << test->name << ":\n"
    << "  " << error.message << "\n\n";
}

void DefaultOutputHandler::run() {
  std::list<Suite*> suites = Suite::all_suites();
  std::list<Suite*>::const_iterator suite;
  for (suite = suites.begin(); suite != suites.end(); suite++) {

    std::list<Test*> tests = (*suite)->get_tests();
    std::list<Test*>::const_iterator test;
    for (test = tests.begin(); test != tests.end(); test++) {
      run_test(*test);
    }
  }
}

} /* namespace */
