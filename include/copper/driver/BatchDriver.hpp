/* BatchDriver.hpp -- Outputs test results to stdout and stderr
 * Copyright (C) 2010 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_BATCH_DRIVER_HPP
#define COPPER_BATCH_DRIVER_HPP

namespace Copper
{

class BatchDriver
{
public:
	static int
	run(int argc, char **argv);
};

}

#endif
