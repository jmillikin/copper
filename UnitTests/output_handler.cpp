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

  std::cerr
    << "FAILURE in " << test->suite_name << "::" << test->name << ":\n"
    << test->file_name << ":" << failure.line << ":"
    << " " << failure.error << "\n\n";
}

void DefaultOutputHandler::error(const Test* test,
  const ErrorException& error) throw () {

  ++num_errors;

  std::cerr
    << "ERROR  in " << test->suite_name << "::" << test->name << ":\n"
    << test->file_name << ":"
    << " " << error.message << "\n\n";
}

} /* namespace */
