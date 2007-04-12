/* test.hpp -- Runs a single unit test
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_HPP
#define COPPER_TEST_HPP

#include <copper/assertion.hpp>
#include <copper/suite.hpp>
#include <copper/util/list.hpp>
#include <copper/util/string.hpp>

namespace Copper {

class Test {
public:
  Test(
    const String& name,
    Suite* suite,
    const String& file_name) throw ();
  virtual ~Test();

  /** Get a list of all tests */
  static List<Test> all();

  /** Run the test */
  virtual void run() = 0;

  /** The name of this test */
  const String name;

  /** The suite this test is part of */
  const Suite* suite;

  /** The file this test's implementation is in */
  const String file_name;

protected:
  /** Used for assert(throws()) */
  bool exception_thrown;

private:
  Test& operator= (const Test&) throw ();
  Test (const Test&) throw ();
};

} /* Namespace */

#endif /* COPPER_TEST_HPP */
