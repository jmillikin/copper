#include "output_handler.h"
#include "test.h"
#include <cstdio>

namespace UnitTests {

void DefaultOutputHandler::pass(const Test*) throw() {
  /* do nothing */
}

void DefaultOutputHandler::fail(const Test* test, const char* message) throw() {
  /* Output to stderr */

  fprintf(stderr, "Test '%s::%s' failed: %s\n", test->suite_name, test->name,
    message);
}

} /* namespace */