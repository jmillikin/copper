/* main.cpp -- Runs an output handler
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/driver/BatchDriver.hpp>

int
main (int argc, char** argv)
{
	Copper::BatchDriver driver;
	return driver.run(argc, argv);
}
