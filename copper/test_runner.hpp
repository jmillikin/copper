/* test_runner.hpp -- Functions for safely and portably running a test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_RUNNER_HPP
#define COPPER_TEST_RUNNER_HPP

#include <copper/test.hpp>
#include <copper/error.hpp>

namespace Copper
{
	/**
	 * Execute a test. This function runs a test, usually in a restricted
	 * environment or in a different process for safety reasons.
	 * 
	 * @param test The test to run.
	 * @param protect Whether protectors should wrap the test's execution.
	 * @param failure This parameter will be set if a failure occurs.
	 * @param error This parameter will be set if an error occurs.
	 */
	void
	exec_test (Test *test,
	           bool protect,
	           Assertion **failure,
	           Error **error);
}

#endif /* COPPER_TEST_RUNNER_HPP */
