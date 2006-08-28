#include <list>
#include "test.h"
#include "suite.h"
#include "output_handlers/default_output_handler.h"
#include "failure_exception.h"
#include "protectors/exception_protector.h"

namespace UnitTests {

Test::Test(
  const std::string& _name,
  Suite* _suite,
  const std::string& _file_name) throw ():
  name(_name),
  suite(_suite),
  file_name(_file_name) {

  _suite->add_test(this);
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

  Test::run_all(&handler, catch_exceptions);

  return 0;
}
