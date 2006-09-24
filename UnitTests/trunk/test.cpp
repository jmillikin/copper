#include "test.h"
#include "suite.h"

namespace UnitTests {

Test::Test(
  const char* _name,
  Suite* _suite,
  const char* _file_name) throw ():

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

#include "output_handlers/default_output_handler.h"
int main(int argc, char** argv) {
  // Where output will be directed to
  DefaultOutputHandler output(argc, argv);
  output.run();

  return 0;
}
