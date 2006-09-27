/* assertion.h - Asserts that certain statements are true
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "failure_exception.h"
#include "assertions.h"

#ifndef ASSERTION_H
#define ASSERTION_H


// Some macros for easier calling of assert() and failed()
#define assert(ASSERTION) assert_func(#ASSERTION, (ASSERTION), __LINE__)

#define failed(ASSERTION) failed_func(#ASSERTION, (ASSERTION))

// Macro for checking if an exception was thrown
/*
#define assert_throws(CODE, EXCEPTION_TYPE) \
  try {\
    CODE;\
    assert_func("assert_throws("#CODE", "#EXCEPTION_TYPE")",\
      std::string(#CODE" threw no exceptions"), __LINE__);\
  }\
  catch (const EXCEPTION_TYPE&) {}
*/
#define assert_throws(CODE, EXCEPTION_TYPE) \
  assert_func("assert_throws unimplemented", false, __LINE__)

#endif /* ASSERTION_H */
