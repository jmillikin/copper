#include "test.h"
#include "fixture.h"

// for strdup, in test 'string_equals'
#include <cstring>

TEST_SUITE(sample_suite)

TEST(assert_failed)
  // Check that a failed test will result in a pass
  assert(failed(false));

  // Check that a passing test will result in a fail
  assert(failed(failed(true)));
}

TEST(integer_equals)
  assert(equal(2, 2));
  assert(failed(equal(1, 2)));
}

TEST(char_string_equals)
  std::string _var1("test"), _var2("test"), _var3("other");
  const char
    *var1 = _var1.c_str(),
    *var2 = _var2.c_str(),
    *var3 = _var3.c_str();

  // Confirm that the addresses are not being compared
  // Can't use unequal for this
  assert(var1 != var2);

  assert(equal(var1, var2));
  assert(failed(equal(var1, var3)));
}

TEST(equal_within)
  assert(equal_within(2.0, 2.0001, 0.001));
  assert(failed(equal_within(2.0, 2.01, 0.001)));
}

TEST(unequal)
  assert(unequal(1, 2));
  assert(failed(unequal(2, 2)));
}

TEST(is_null)
  int* var1 = 0, var2;
  assert(null(var1));
  assert(failed(null(&var2)));
}

TEST(not_null)
  int* var1 = 0, var2;
  assert(not_null(&var2));
  assert(failed(not_null(var1)));
}

TEST(greater_than)
  assert(greater_than(2, 1));

  assert(failed(greater_than(2, 2)));
  assert(failed(greater_than(2, 3)));
}

TEST(greater_than_or_equal)
  assert(greater_than_or_equal(2, 2));
  assert(greater_than_or_equal(2, 1));

  assert(failed(greater_than_or_equal(1, 2)));
}

TEST(less_than)
  assert(less_than(1, 2));

  assert(failed(less_than(2, 2)));
  assert(failed(less_than(2, 1)));
}

TEST(less_than_or_equal)
  assert(less_than_or_equal(1, 2));
  assert(less_than_or_equal(2, 2));

  assert(failed(less_than_or_equal(2, 1)));
}

class TestException {
public:
  TestException() throw () {}
  ~TestException() throw() {}
};

TEST(thrown_exception)
  throw TestException();
}

/*
TEST(expected_exceptions)
  bool caught_TestException = false;
  try {
    throw TestException();
  }

  catch (const TestException& e){
    caught_TestException = true;
  }

  if (!caught_TestException){
    fail("Failed to catch TestException");
  }
}
*/

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
  assert(equal(fixture_var, 1));
  assert(set_up_finished);
}

}
