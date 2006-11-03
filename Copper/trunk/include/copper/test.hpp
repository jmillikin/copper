/* test.hpp -- Runs a single unit test
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef COPPER_TEST_HPP
#define COPPER_TEST_HPP

#include <copper/assertion.hpp>
#include <copper/suite.hpp>

namespace Copper {

class OutputHandler;

class Test {
public:
  Test(
    const char* name,
    Suite* suite,
    const char* file_name) throw ();
  virtual ~Test();

  /** Run the test */
  Assertion* run();

  /** The name of this test */
  const char* name;

  /** The suite this test is part of */
  const Suite* suite;

  /** The file this test's implementation is in */
  const char* file_name;

protected:
  /** Run the user's test code */
  virtual void _run(Copper::Assertion** bad_assertion) = 0;

  /** Used to set up this test's fixture, if it exists */
  virtual void set_up() = 0;

  /** Used to tear down this test's fixture, if it exists */
  virtual void tear_down() = 0;
};

} /* Namespace */

#endif /* COPPER_TEST_HPP */
