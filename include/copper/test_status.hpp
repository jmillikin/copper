/* test_status.hpp -- Manages the status of a running test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_STATUS_HPP
#define COPPER_TEST_STATUS_HPP

#include <copper/assertion.hpp>
#include <copper/assertion_result.hpp>

namespace Copper {

typedef void (FailureHandler)(const Assertion& failure, void *data);

void
do_assert (const AssertionResult& result,
           const String& text,
           const unsigned int line) throw ();

void
do_fail_test (const String& text, const unsigned int line) throw ();

void
set_failure_handler (FailureHandler *handler, void *data);

}

#endif
