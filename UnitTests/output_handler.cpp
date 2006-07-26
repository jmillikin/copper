#include "output_handler.h"
#include "test.h"
#include <iostream>

namespace UnitTests {

DefaultOutputHandler::DefaultOutputHandler() throw():
  passed(0), failed(0){}

DefaultOutputHandler::~DefaultOutputHandler() throw(){
  // Print statistics
  std::cout<< passed << " tests passed\n" << failed << " tests failed\n";
}

void DefaultOutputHandler::pass(const Test*) throw(){
  ++passed;
}

void DefaultOutputHandler::fail(const Test* test, const std::string& message)
  throw() {

  ++failed;

  std::cerr << test->suite_name << "::" << test->name << " failed: "
    << message << "\n";
}

} /* namespace */
