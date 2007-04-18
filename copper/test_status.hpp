/* test_status.hpp -- Manages the status of a running test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_STATUS_HPP
#define COPPER_TEST_STATUS_HPP

#include <copper/failure.hpp>
#include <copper/assertion_result.hpp>

namespace Copper
{
	typedef void (FailureHandler)(const Failure &failure, void *data);

	void
	do_assert (const AssertionResult &result,
	           const char *text,
	           const char *file,
	           const unsigned int line);

	void
	do_assert ();

	void
	do_fail_test (const char *text,
	              const char *message,
	              const char *file,
	              const unsigned int line);

	void
	do_fail_test (const char *message,
	              const char *file,
	              const unsigned int line);

	AssertionResult
	do_failed (const AssertionResult &result,
	           const char *text);

	void
	set_failure_handler (FailureHandler *new_handler, void *data);
}

#endif
