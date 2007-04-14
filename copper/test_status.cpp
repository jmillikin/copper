/* test_status.cpp -- Manages the status of a running test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <assert.h>

#include <copper/test_status.hpp>
#include "export.hpp"

namespace Copper
{
	FailureHandler *handler = NULL;
	void *handler_data = NULL;

	void
	do_assert (const bool, const int)
	{
	}

	EXPORT
	void
	do_assert (const AssertionResult &result,
	           const String &text,
	           const unsigned int line)
	{
		assert (handler != NULL);

		if (!result.passed ())
		{
			handler (Assertion (result, text, line), handler_data);
		}
	}

	EXPORT
	void
	do_fail_test (const String &message, const unsigned int line)
	{
		do_fail_test ("", message, line);
	}

	EXPORT
	void
	do_fail_test (const String &text,
	              const String &message,
	              const unsigned int line)
	{
		assert (handler != NULL);
		handler (Assertion (false, text, message, line), handler_data);
	}

	EXPORT
	void
	set_failure_handler (FailureHandler *new_handler, void *data)
	{
		handler = new_handler;
		handler_data = data;
	}

}
