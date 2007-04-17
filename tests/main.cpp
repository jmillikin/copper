/* main.cpp -- Runs an output handler
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/default_output_handler.hpp>

int
main (int argc, char** argv)
{
	// Output to the console
	Copper::DefaultOutputHandler output (argc, argv);
	return output.run ();
}
