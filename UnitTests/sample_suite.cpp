#include "test.h"
#include "fixture.h"

// for strdup, in test 'string_equals'
#include <cstring>

TEST_SUITE(sample_suite)

TEST(assert_failed)
  // Check that a failed test will result in a pass
  assert_failed(assert(false).is_true());

  // Check that a passing test will result in a fail
  assert_failed(assert_failed(assert(true).is_true()));
}

TEST(integer_equals)
  assert(2).equals(2);
}

TEST(char_string_equals)
  std::string var1("test"), var2("test");

  // Confirm that the addresses are not being compared
  // Can't use not_equal for this
  assert(var1.c_str() != var2.c_str()).is_true();

  assert(var1.c_str()).equals(var2.c_str());
}

TEST(not_equal)
  assert(2).not_equals(3);
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

TEST(between)
  assert(2).between(1, 3);
}

TEST(between_inclusive)
  assert(2).between_inclusive(1, 3);
  assert(2).between_inclusive(2, 3);
}

TEST(is_true)
  assert(true).is_true();
}

TEST(is_false)
  assert(false).is_false();
}

class TestException {
public:
  TestException() throw () {}
  ~TestException() throw() {}
};

TEST(expected_exceptions)
  throw TestException();
/*
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
*/
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
