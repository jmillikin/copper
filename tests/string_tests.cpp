/* string_tests.cpp - Tests of equal() and unequal() on strings
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <copper.hpp>
#include <cstring>
#include <cstdlib>

TEST_SUITE("String tests") {

FIXTURE(str_fixture) {
  const Copper::String
    var1 = "test",
    var2 = "test",
    var3 = "other",
    var4 = "other";
  char* cvar1, *cvar2, *cvar3, *cvar4;

  SET_UP {
    cvar1 = Copper::strdup(var1.c_str());
    cvar2 = Copper::strdup(var2.c_str());
    cvar3 = Copper::strdup(var3.c_str());
    cvar4 = Copper::strdup(var4.c_str());
  }

  TEAR_DOWN {
    std::free(cvar1);
    std::free(cvar2);
    std::free(cvar3);
    std::free(cvar4);
  }
}

FIXTURE_TEST("Copper::String equal", str_fixture) {
  assert(equal(var1, var2));
}

FIXTURE_TEST("Copper::String equal fail", str_fixture) {
  assert(failed(equal(var1, var3)));
}

FIXTURE_TEST("char* equal", str_fixture) {
  // Confirm that the addresses are not being compared
  assert(cvar1 != cvar2);

  assert(equal("test", "test"));
  assert(equal(cvar1, "test"));
  assert(equal(cvar1, cvar2));
}

FIXTURE_TEST("char* equal fail", str_fixture) {
  assert(failed(equal(cvar1, cvar3)));
}

FIXTURE_TEST("mixed string equality", str_fixture) {
  assert(equal(var1, cvar1));
  assert(equal(var2, cvar1));
}

FIXTURE_TEST("mixed string equality fail", str_fixture) {
  assert(failed(equal(var1, cvar3)));
}

FIXTURE_TEST("Copper::String unequal", str_fixture) {
  assert(unequal(var1, var3));
}

FIXTURE_TEST("Copper::String unequal fail", str_fixture) {
  assert(failed(unequal(var3, var4)));
}

FIXTURE_TEST("char* unequal", str_fixture) {
  assert(unequal("test", "other"));
  assert(unequal(cvar1, "other"));
  assert(unequal(cvar1, cvar3));
}

FIXTURE_TEST("char* unequal fail", str_fixture) {
  assert(failed(unequal(cvar3, cvar4)));
}

FIXTURE_TEST("mixed string inequality", str_fixture) {
  assert(unequal(var1, cvar3));
}

FIXTURE_TEST("mixed string inequality fail", str_fixture) {
  assert(failed(unequal(var1, cvar2)));
}

}