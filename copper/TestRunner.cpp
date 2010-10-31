/* TestRunner.cpp -- Runs a list of tests and reports the results
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include <copper/TestRunner.hpp>

namespace Copper {

void
TestRunner::RunTests (OutputHandler *output,
                      const List<Test> &tests,
                      const List<Protector> &protectors)
{
	const ListNode<Test> *node = NULL;
	while (tests.each (&node))
	{ RunTest (output, node->value, protectors); }
}

void
TestRunner::RunTest (OutputHandler *output,
                     Test *test,
                     const List<Protector> &protectors)
{
	// TODO
}

}
