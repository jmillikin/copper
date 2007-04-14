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

	EXPORT
	void
	do_assert (const AssertionResult &result,
	           const char *text,
	           const char *file,
	           const unsigned int line)
	{
		if (!result.passed ())
		{
			do_fail_test (text, result->failure_message.c_str (),
			              file, line);
		}
	}

	void
	do_assert ()
	{
	}

	EXPORT
	void
	do_fail_test (const char *text,
	              const char *message,
	              const char *file,
	              const unsigned int line)
	{
		assert (handler != NULL);
		handler (Failure (text, message, file, line), handler_data);
	}

	EXPORT
	void
	do_fail_test (const char *message,
	              const char *file,
	              const unsigned int line)
	{
		do_fail_test ("", message, file, line);
	}

	EXPORT
	void
	set_failure_handler (FailureHandler *new_handler, void *data)
	{
		handler = new_handler;
		handler_data = data;
	}
}
