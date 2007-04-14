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
	/**
	 * A function that will be called whenever a failure is encountered
	 * while running a test. See set_failure_handler().
	 * 
	 * @param failure The failure that occurred.
	 * @param data User-defined data passed to set_failure_handler().
	 */
	typedef void (FailureHandler)(const Failure &failure, void *data);

	/**
	 * Check that an assertion was true. If it was not true, the current
	 * failure handler will be executed.
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
	           const unsigned int line);

	/** For assert (throws ()) only, do not use */
	void
	do_assert ();

	/**
	 * Forces the current test to fail.
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
	              const unsigned int line);

	/**
	 * Forces the current test to fail. This is an overloaded version, for
	 * use when the user has called fail_test ().
	 * 
	 * @param message The failure message, to be displayed to the user.
	 * @param file The file this function is being called from.
	 * @param line The line of the file this function is being called from.
	 */
	void
	do_fail_test (const char *message,
	              const char *file,
	              const unsigned int line);

	/**
	 * Check that an assertion was false. If it was true, the current
	 * failure handler will be executed.
	 * 
	 * @param result The result of the assertion.
	 * @param text The code that this Assertion tests.
	 */
	AssertionResult
	do_failed (const AssertionResult &result,
	           const char *text);

	/**
	 * Set the current failure handler function. This should be called once,
	 * before a test is executed.
	 * 
	 * @param handler The handler function to be called on failure.
	 * @param data User-defined data, which will be passed to the handler.
	 */
	void
	set_failure_handler (FailureHandler *handler, void *data);
}

#endif
