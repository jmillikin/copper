/* format_tests.cpp - Test behaviour of the format() function
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper.hpp>

using Copper::format;

// Can't use normal limits, since they change from system to system
const signed short MY_SHRT_MIN = -32768;
const signed short MY_SHRT_MAX = 32767;

const unsigned short MY_USHRT_MAX = 65535;

const signed int MY_INT_MAX = 2147483647;
const signed int MY_INT_MIN = -MY_INT_MAX - 1;

const unsigned int MY_UINT_MAX = 4294967295U;

const signed long MY_LONG_MAX = 2147483647L;
const signed long MY_LONG_MIN = -MY_LONG_MAX - 1;

const unsigned long MY_ULONG_MAX = 4294967295UL;

TEST_SUITE(format_tests) {

TEST("bool test") {
  assert(equal("true", format(true)));
  assert(equal("false", format(false)));
}

TEST("char test") {
  /* Bad characters */
  for (char ii = '\0'; ii < ' '; ii++) {
    assert(equal("", format(ii)));
  }
  /* 0x7F = DEL */
  assert(equal("", format('\x7F')));

  char buffer[2];
  buffer[1] = '\0';

  for (buffer[0] = ' '; buffer[0] < '~'; buffer[0]++) {
    assert(equal(buffer, format(buffer[0])));
  }
}

TEST("signed short test") {
  signed short neg_one = -1, pos_one = 1, zero = 0;
  assert(equal("-1", format(neg_one)));
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* Check limits */
  assert(equal("-32768", format(MY_SHRT_MIN)));
  assert(equal("32767", format(MY_SHRT_MAX)));
}

TEST("unsigned short test") {
  unsigned short pos_one = 1, zero = 0;
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* Check limits */
  assert(equal("65535", format(MY_USHRT_MAX)));
}

TEST("signed int test") {
  signed int neg_one = -1, pos_one = 1, zero = 0;
  assert(equal("-1", format(neg_one)));
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* Check limits */
  assert(equal("-2147483648", format(MY_INT_MIN)));
  assert(equal("2147483647", format(MY_INT_MAX)));
}

TEST("unsigned int test") {
  unsigned int pos_one = 1, zero = 0;
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* Check limits */
  assert(equal("4294967295", format(MY_UINT_MAX)));
}

TEST("signed long test") {
  signed long neg_one = -1, pos_one = 1, zero = 0;
  assert(equal("-1", format(neg_one)));
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* Check limits */
  assert(equal("-2147483648", format(MY_LONG_MIN)));
  assert(equal("2147483647", format(MY_LONG_MAX)));
}

TEST("unsigned long test") {
  unsigned long pos_one = 1, zero = 0;
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* Check limits */
  assert(equal("4294967295", format(MY_ULONG_MAX)));
}

TEST("float test") {
  assert(equal("1.2345", format(1.2345f)));
}

TEST("double test") {
  assert(equal("1.2345", format(1.2345)));
}

TEST("Copper::String test") {
  assert(equal("some_string", format(Copper::String("some_string"))));
}

}
