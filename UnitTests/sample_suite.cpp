#include "test.h"
#include "fixture.h"

// for strdup, in test 'string_equals'
#include <cstring>

TEST_SUITE(suite1)

TEST(integer_equals)
  int var = 2;
  assert(var).equals(2);
}

TEST(string_equals)
  char* var1 = strdup("test");
  char* var2 = strdup("test");

  // Confirm that the addresses are not being compared
  // Can't use not_equal for this
  assert(var1 != var2).is_true();

  assert(var1).equals(var2);

  free(var1);
  free(var2);
}

TEST(not_equal)
  assert(2).not_equal(3);
}

TEST(is_null)
  assert(0).is_null();
}

TEST(not_null)
  int var;
  assert(&var).not_null();
}

TEST(nearly_equals)
  float var = 2.0f;
  assert(var).nearly_equals(2.0001f, 0.001f);
}

TEST(greater_than)
  assert(3).greater_than(2);
}

TEST(greater_than_or_equal)
  assert(4).greater_than_or_equal(4);
  assert(4).greater_than_or_equal(3);
}

TEST(less_than)
  assert(10).less_than(12);
}

TEST(less_than_or_equal)
  assert(9).less_than_or_equal(9);
  assert(9).less_than_or_equal(10);
}

TEST(is_true)
  assert(true).is_true();
}

TEST(is_false)
  assert(false).is_false();
}

FIXTURE(the_fixture)

void set_up(){
  fixture_var = 1;
  set_up_finished = true;
}

// If desired, include a "void tear_down(){...

int fixture_var;
bool set_up_finished;

};

FIXTURE_TEST(fixture_test, the_fixture)
  assert(fixture_var).equals(1);
  assert(set_up_finished).is_true();
}

}
