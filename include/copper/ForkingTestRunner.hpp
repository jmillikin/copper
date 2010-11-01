/* ForkingTestRunner.hpp -- Runs each test in a separate process
 * Copyright (C) 2009 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_FORKING_TEST_RUNNER_HPP
#define COPPER_FORKING_TEST_RUNNER_HPP

#include <copper/TestRunner.hpp>
#include <copper/FuncAttrs.hpp>

namespace Copper {

class COPPER_FUNCATTR_EXPORT ForkingTestRunner : public TestRunner
{
public:
	void
	RunTest (OutputHandler &output,
	         Test &test,
	         const List<Protector> &protectors);
};

}

#endif
