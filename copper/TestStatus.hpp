/* test_status.hpp -- Manages the status of a running test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_STATUS_HPP
#define COPPER_TEST_STATUS_HPP

#include <copper/AssertionResult.hpp>
#include <copper/Failure.hpp>
#include <copper/FuncAttrs.hpp>

namespace Copper
{
	typedef void (FailureHandler)(const Failure &failure, void *data);

	COPPER_FUNCATTR_EXPORT
	void
	do_assert (const AssertionResult &result,
	           const char *text,
	           const char *file,
	           const unsigned int line);

	COPPER_FUNCATTR_EXPORT
	void
	do_assert (const bool passed,
	           const char *text,
	           const char *file,
	           const unsigned int line);

	COPPER_FUNCATTR_EXPORT
	void
	do_assert ();

	COPPER_FUNCATTR_EXPORT
	void
	do_fail_test (const char *text,
	              const char *message,
	              const char *file,
	              const unsigned int line);

	COPPER_FUNCATTR_EXPORT
	void
	do_fail_test (const char *message,
	              const char *file,
	              const unsigned int line);

	COPPER_FUNCATTR_EXPORT
	AssertionResult
	do_failed (const AssertionResult &result,
	           const char *text);

	COPPER_FUNCATTR_EXPORT
	AssertionResult
	do_failed (const bool passed,
	           const char *text);

	COPPER_FUNCATTR_EXPORT
	void
	set_failure_handler (FailureHandler *new_handler, void *data);
}

#endif
