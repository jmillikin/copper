/* main.cpp -- Runs an output handler
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "output_handler.hpp"

int main(int argc, char** argv) {
  // Output to the console
  OutputHandler output(argc, argv);
  return output.run();
}
