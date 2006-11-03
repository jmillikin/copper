/* main.cpp -- Runs an output handler
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper/default_output_handler.hpp>

int main(int argc, char** argv) {
  // Where output will be directed to
  Copper::DefaultOutputHandler output(argc, argv);
  return output.run();
}
