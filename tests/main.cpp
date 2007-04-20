/* main.cpp -- Runs an output handler
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstdlib>
#include <copper/default_output_handler.hpp>

Copper::DefaultOutputHandler *output;

void
do_exit ()
{
	delete output;
}

int
main (int argc, char** argv)
{
	atexit (do_exit);

	// Output to the console
	output = new Copper::DefaultOutputHandler (argc, argv);
	return output->run ();
}
