#include "output_handlers/default_output_handler.h"

int main(int argc, char** argv) {
  // Where output will be directed to
  UnitTests::DefaultOutputHandler output(argc, argv);
  output.run();

  return 0;
}
