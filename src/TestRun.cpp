/* TestRun.cpp -- Information on one run of a test
 * Copyright (C) 2009 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/TestRun.hpp>
#include <copper/Test.hpp>
#include <copper/AssertionResult.hpp>

namespace Copper {

TestRun::TestRun (Test *test): test (test) {}

TestRun::~TestRun () {}

bool
TestRun::Assert (bool result,
                 const char *text,
                 const char *file,
                 unsigned int line)
{
	if (result) { return true; }
	Assert (AssertionResult::fail ("Boolean assertion failed"), text, file, line);
}

void
TestRun::Run ()
{
	test->Run (this);
}

}
