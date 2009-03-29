/* test_status.cpp -- Manages the status of a running test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cassert>

#include <copper/TestStatus.hpp>

namespace Copper
{
	/** @var FailureHandler
	 * A function that will be called whenever a failure is encountered
	 * while running a test.
	 * 
	 * @see set_failure_handler ()
	 * 
	 * @param failure The failure that occurred.
	 * @param data User-defined data passed to set_failure_handler().
	 */

	FailureHandler *handler = NULL;
	void *handler_data = NULL;

	/**
	 * Check that an assertion was true. If it was not true, the current
	 * failure handler will be executed.
	 * 
	 * @see ASSERT ()
	 * 
	 * @param result The result of the assertion.
	 * @param text The code that this Assertion tests.
	 * @param file The name of the file containing the assertion.
	 * @param line The line the assertion is located on.
	 */
	void
	do_assert (const AssertionResult &result,
	           const char *text,
	           const char *file,
	           const unsigned int line)
	{
		if (!result.passed)
		{
			do_fail_test (text, result.failure_message.CStr (),
			              file, line);
		}
	}

	/**
	 * Check that a boolean value is true. If it is not true, the current
	 * failure handler will be executed.
	 * 
	 * @see ASSERT ()
	 * 
	 * @param passed Whether the assertion passed.
	 * @param text The code that this Assertion tests.
	 * @param file The name of the file containing the assertion.
	 * @param line The line the assertion is located on.
	 */
	void
	do_assert (const bool passed,
	           const char *text,
	           const char *file,
	           const unsigned int line)
	{
		if (!passed)
		{
			do_fail_test (text, "Boolean assertion failed",
			              file, line);
		}
	}

	/**
	 * @brief For internal use only, do not use
	 */
	void
	do_assert ()
	{
	}

	/**
	 * Forces the current test to fail.
	 * 
	 * @see fail_test ()
	 * 
	 * @param text The text that should be displayed as the assertion text.
	 * @param message The failure message, to be displayed to the user.
	 * @param file The file this function is being called from.
	 * @param line The line of the file this function is being called from.
	 */
	void
	do_fail_test (const char *text,
	              const char *message,
	              const char *file,
	              const unsigned int line)
	{
		assert (handler != NULL);
		handler (Failure (text, message, file, line), handler_data);
	}

	/**
	 * Forces the current test to fail. This is an overloaded version, for
	 * use when the user has called fail_test ().
	 * 
	 * @see fail_test ()
	 * 
	 * @param message The failure message, to be displayed to the user.
	 * @param file The file this function is being called from.
	 * @param line The line of the file this function is being called from.
	 */
	void
	do_fail_test (const char *message,
	              const char *file,
	              const unsigned int line)
	{
		do_fail_test ("", message, file, line);
	}

	/**
	 * Set the current failure handler function. This should be called once,
	 * before a test is executed.
	 * 
	 * @see FailureHandler
	 * 
	 * @param new_handler The handler function to be called on failure.
	 * @param data User-defined data, which will be passed to the handler.
	 */
	void
	set_failure_handler (FailureHandler *new_handler, void *data)
	{
		handler = new_handler;
		handler_data = data;
	}
}
