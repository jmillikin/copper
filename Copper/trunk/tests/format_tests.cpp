/* format_tests.cpp - Test behaviour of the format() function
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper.hpp>

using Copper::format;

TEST_SUITE(format_tests) {

TEST(bool_test) {
  assert(equal("true", format(true)));
  assert(equal("false", format(false)));
}

TEST(char_test) {
  /* Bad characters */
  for (int ii = 0; ii < 32 /* Check characters before ' ' */; ii++) {
    assert(equal("", format(static_cast<char>(ii))));
  }
  /* 127 = DEL */
  assert(equal("", format('\127')));

  char buffer[2];
  buffer[1] = '\0';

  for (int ii = 32; ii < 127; ii++) {
    buffer[0] = static_cast<char>(ii);
    assert(equal(buffer, format(buffer[0])));
  }
}

TEST(signed_short_test) {
  signed short neg_one = -1, pos_one = 1, zero = 0;
  assert(equal("-1", format(neg_one)));
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* TODO: check limits */
  fail("Check limits of signed short");
}

TEST(unsigned_short_test) {
  unsigned short pos_one = 1, zero = 0;
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* TODO: check limits */
  fail("Check limits of unsigned short");
}

TEST(signed_int_test) {
  signed int neg_one = -1, pos_one = 1, zero = 0;
  assert(equal("-1", format(neg_one)));
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* TODO: check limits */
  fail("Check limits of signed int");
}

TEST(unsigned_int_test) {
  unsigned int pos_one = 1, zero = 0;
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* TODO: check limits */
  fail("Check limits of unsigned int");
}

TEST(signed_long_test) {
  signed long neg_one = -1, pos_one = 1, zero = 0;
  assert(equal("-1", format(neg_one)));
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* TODO: check limits */
  fail("Check limits of signed long");
}

TEST(unsigned_long_test) {
  unsigned long pos_one = 1, zero = 0;
  assert(equal("1", format(pos_one)));
  assert(equal("0", format(zero)));

  /* TODO: check limits */
  fail("Check limits of unsigned long");
}

TEST(float_test) {
  assert(equal("1.2345", format(1.2345f)));
}

TEST(double_test) {
  assert(equal("1.2345", format(1.2345)));
}

TEST(Copper_String_test) {
  assert(equal("some_string", format(Copper::String("some_string"))));
}

}
