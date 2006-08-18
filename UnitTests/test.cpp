#include "test.h"
#include "test_registry.h"
#include "output_handler.h"
#include "failure_exception.h"

namespace UnitTests {

Test::Test(
  const std::string& _name,
  const std::string& _suite_name) throw ():
  name(_name),
  suite_name(_suite_name) {

  TestRegistry::add(this);
}

Test::~Test() {}

void Test::run() {
  set_up();
  _run();
  tear_down();
}

} // namespace

using namespace UnitTests;

int main(int argc, char** argv) {
  DefaultOutputHandler handler;
  bool catch_exceptions = true;
  if (argc > 1) {
    if (strcmp(argv[1], "--no-exceptions") == 0) {
      catch_exceptions = false;
    }
  }

  TestRegistry::run_all(&handler, catch_exceptions);

  return 0;
}
