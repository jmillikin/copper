/* BatchDriver.hpp -- Outputs test results to stdout and stderr
 * Copyright (C) 2010 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_BATCH_DRIVER_HPP
#define COPPER_BATCH_DRIVER_HPP

#include <copper/FuncAttrs.hpp>

namespace Copper
{

class COPPER_FUNCATTR_EXPORT BatchDriver
{
public:
	static int
	run(int argc, char **argv);
};

}

#endif
