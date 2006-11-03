/* fixture.hpp - Allows easy sharing of data between tests
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef FIXTURE_HPP
#define FIXTURE_HPP

namespace UnitTests {

class Fixture {
public:
  Fixture();
  virtual ~Fixture();

protected:
  virtual void set_up();
  virtual void tear_down();
};

} /* namespace */

#endif /* FIXTURE_HPP */
