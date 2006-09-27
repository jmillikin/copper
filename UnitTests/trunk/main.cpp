/* main.cpp -- Runs an output handler
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "output_handlers/default_output_handler.hpp"

int main(int argc, char** argv) {
  // Where output will be directed to
  UnitTests::DefaultOutputHandler output(argc, argv);
  output.run();

  return 0;
}
