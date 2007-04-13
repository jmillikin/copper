/* string_tests.cpp - Tests of equal() and unequal() on strings
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>
#include <cstring>
#include <cstdlib>

TEST_SUITE(string_tests) {

TEST (construct_with_size)
{
	Copper::String a ("test", 3), b ("test", 5);
	assert (equal ("tes", a));
	assert (equal ("test", b));
}

FIXTURE(str_fixture) {
  const Copper::String
    var1 = "test",
    var2 = "test",
    var3 = "other",
    var4 = "other";
  char* cvar1, *cvar2, *cvar3, *cvar4;

  SET_UP {
    cvar1 = Copper::strndup(var1.c_str());
    cvar2 = Copper::strndup(var2.c_str());
    cvar3 = Copper::strndup(var3.c_str());
    cvar4 = Copper::strndup(var4.c_str());
  }

  TEAR_DOWN {
    std::free(cvar1);
    std::free(cvar2);
    std::free(cvar3);
    std::free(cvar4);
  }
}

FIXTURE_TEST(Copper_String_equal, str_fixture) {
  assert(equal(var1, var2));
}

FIXTURE_TEST(Copper_String_equal_fail, str_fixture) {
  assert(failed(equal(var1, var3)));
}

FIXTURE_TEST(char_star_equal, str_fixture) {
  // Confirm that the addresses are not being compared
  assert(cvar1 != cvar2);

  assert(equal("test", "test"));
  assert(equal(cvar1, "test"));
  assert(equal(cvar1, cvar2));
}

FIXTURE_TEST(char_star_equal_fail, str_fixture) {
  assert(failed(equal(cvar1, cvar3)));
}

FIXTURE_TEST(mixed_string_equality, str_fixture) {
  assert(equal(var1, cvar1));
  assert(equal(var2, cvar1));
}

FIXTURE_TEST(mixed_string_equality_fail, str_fixture) {
  assert(failed(equal(var1, cvar3)));
}

FIXTURE_TEST(Copper_String_unequal, str_fixture) {
  assert(unequal(var1, var3));
}

FIXTURE_TEST(Copper_String_unequal_fail, str_fixture) {
  assert(failed(unequal(var3, var4)));
}

FIXTURE_TEST(char_star_unequal, str_fixture) {
  assert(unequal("test", "other"));
  assert(unequal(cvar1, "other"));
  assert(unequal(cvar1, cvar3));
}

FIXTURE_TEST(char_star_unequal_fail, str_fixture) {
  assert(failed(unequal(cvar3, cvar4)));
}

FIXTURE_TEST(mixed_string_inequality, str_fixture) {
  assert(unequal(var1, cvar3));
}

FIXTURE_TEST(mixed_string_inequality_fail, str_fixture) {
  assert(failed(unequal(var1, cvar2)));
}

TEST(compare_to_NULL) {
  assert(unequal("test", (char*)0));
  assert(failed(equal("test", (char*)0)));
}

}
