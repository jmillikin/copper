/* main.cpp -- Runs an output handler
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstdlib>
#include <copper/DefaultOutputHandler.hpp>

Copper::OutputHandler *output;

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
