#include "output_handler.h"
#include "test.h"
#include <iostream>

namespace UnitTests {

void DefaultOutputHandler::pass(const Test*) throw() {
  /* do nothing */
}

void DefaultOutputHandler::fail(const Test* test, const std::string& message)
  throw() {

  std::cerr << test->suite_name << "::" << test->name << " failed: "
    << message << "\n";
}

} /* namespace */
