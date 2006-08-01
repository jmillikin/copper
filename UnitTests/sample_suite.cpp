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
  assert_failed(assert(1).equals(2));
}

TEST(char_string_equals)
  std::string var1("test"), var2("test"), var3("other");

  // Confirm that the addresses are not being compared
  // Can't use not_equal for this
  assert(var1.c_str() != var2.c_str()).is_true();

  assert(var1.c_str()).equals(var2.c_str());
  assert_failed(assert(var1.c_str()).equals(var3.c_str()));
}

TEST(not_equal)
  assert(2).not_equals(3);
  assert_failed(assert(2).not_equals(2));
}

TEST(is_null)
  int var;
  assert(0).is_null();
  assert_failed(assert(&var).is_null());
}

TEST(not_null)
  int var;
  assert(&var).not_null();
  assert_failed(assert(0).not_null());
}

TEST(nearly_equals)
  assert(2.0).nearly_equals(2.0001, 0.001);
  assert_failed(assert(2.0).nearly_equals(2.01, 0.001));
}

TEST(greater_than)
  assert(3).greater_than(2);

  assert_failed(assert(2).greater_than(2));
  assert_failed(assert(2).greater_than(3));
}

TEST(greater_than_or_equal)
  assert(4).greater_than_or_equal(4);
  assert(4).greater_than_or_equal(3);

  assert_failed(assert(3).greater_than_or_equal(4));
}

TEST(less_than)
  assert(10).less_than(12);

  assert_failed(assert(10).less_than(10));
  assert_failed(assert(12).less_than(10));
}

TEST(less_than_or_equal)
  assert(9).less_than_or_equal(9);
  assert(9).less_than_or_equal(10);

  assert_failed(assert(10).less_than_or_equal(9));
}

TEST(between)
  assert(2).between(1, 3);

  assert_failed(assert(1).between(2, 3));
  assert_failed(assert(3).between(1, 2));
}

TEST(between_inclusive)
  assert(2).between_inclusive(1, 3);
  assert(2).between_inclusive(2, 3);

  assert_failed(assert(2).between_inclusive(3, 4));
  assert_failed(assert(5).between_inclusive(3, 4));
}

TEST(is_true)
  assert(true).is_true();

  assert_failed(assert(false).is_true());
}

TEST(is_false)
  assert(false).is_false();

  assert_failed(assert(true).is_false());
}

class TestException {
public:
  TestException() throw () {}
  ~TestException() throw() {}
};

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
  assert(fixture_var).equals(1);
  assert(set_up_finished).is_true();
}

}
