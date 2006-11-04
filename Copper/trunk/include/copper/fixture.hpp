/* fixture.hpp - Allows easy sharing of data between tests
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef COPPER_FIXTURE_HPP
#define COPPER_FIXTURE_HPP

namespace Copper {

class Fixture {
public:
  Fixture();
  virtual ~Fixture();

protected:
  virtual void _set_up();
  virtual void _tear_down();
};

} /* namespace */

#endif /* COPPER_FIXTURE_HPP */
