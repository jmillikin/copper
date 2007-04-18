/* test_runner.hpp -- Functions for safely and portably running a test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_RUNNER_HPP
#define COPPER_TEST_RUNNER_HPP

namespace Copper
{
	class Test;
	class Error;
	class Failure;

	void
	exec_test (Test *test,
	           bool protect,
	           Failure **failure,
	           Error **error);
}

#endif /* COPPER_TEST_RUNNER_HPP */
