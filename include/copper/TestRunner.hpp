/* TestRunner.hpp -- Runs a list of tests and reports the results
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_RUNNER_HPP
#define COPPER_TEST_RUNNER_HPP

#include <copper/List.hpp>
#include <copper/FuncAttrs.hpp>

namespace Copper {

class Test;
class TestRun;
class Protector;
class OutputHandler;

class COPPER_FUNCATTR_EXPORT TestRunner
{
public:
	void
	RunTests (OutputHandler &output,
	          const List<Test> &tests,
	          const List<Protector> &protectors);
	
	virtual void
	RunTest (OutputHandler &output,
	         Test &test,
	         const List<Protector> &protectors);
};

}

#endif
