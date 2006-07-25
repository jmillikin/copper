#include "test.h"

TEST_SUITE(suite1)

TEST(integer_equals){
  int var = 2;
  assert(var).equals(2);
}

TEST(nearly_equals){
  float var = 2.0f;
  assert(var).nearly_equals(2.0f, 0.1f);
}

TEST(boolean_test){
  bool var = true;
  assert(var).is_true();
}

TEST(div_by_zero){
  int i = 1, j = 0;
  i = i / j;
}

TEST(string_equality){
  char* var = "test";
  assert(var).equals("test");
}

TEST(failed_assertion){
  assert(2).equals(3);
}

END_TEST_SUITE
