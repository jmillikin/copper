/* test_status.cpp -- Manages the status of a running test
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstdlib>
#include <cstdio>

#include <copper/test_status.hpp>
#include "export.hpp"

namespace Copper {

static Assertion *failed = NULL;

EXPORT bool
do_assert (const AssertionResult& result,
           const String& text,
           const unsigned int line) throw ()
{
	if (failed)
		abort ();

	if (!result.passed())
		failed = new Assertion (result, text, line);

	return !result.passed ();
}

EXPORT void
do_fail_test (const String& text, const unsigned int line) throw ()
{
	if (failed)
		abort ();

	failed = new Assertion (false, "", text, line);
}

EXPORT Assertion *
get_failed () throw ()
{
	return failed;
}

}
