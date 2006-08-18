#include <iostream>
#include "output_handler.h"
#include "test.h"
#include "error_exception.h"

namespace UnitTests {

OutputHandler::OutputHandler() {}

OutputHandler::~OutputHandler() {}

DefaultOutputHandler::DefaultOutputHandler() throw ():
  OutputHandler(),
  num_passed(0),
  num_failed(0),
  num_errors(0) {

  num_errors = 0;
}

DefaultOutputHandler::~DefaultOutputHandler() throw (){
  // Print statistics
  std::cout
    << num_passed << " tests passed\n"
    << num_failed << " tests failed\n"
    << num_errors << " errors\n";
}

void DefaultOutputHandler::begin(const Test*) throw () {}

void DefaultOutputHandler::pass(const Test*) throw (){
  ++num_passed;
}

void DefaultOutputHandler::fail(const Test* test,
  const FailureException& failure) throw () {

  ++num_failed;

  std::cerr << "FAILED:\t" << test->suite_name << "::" << test->name << "\n"
    << "\tassertion '" << failure.assertion << "' (" << failure.line << "):\n"
    << "\t\t" << failure.error
    << "\n====================\n";
}

void DefaultOutputHandler::error(const Test* test,
  const ErrorException& error) throw () {

  ++num_errors;

  std::cerr << "ERROR:\t" << error.message << "\n"
    << "\tIn " << test->suite_name << "::" << test->name
    << "\n====================\n";
}

} /* namespace */
