#ifndef FIXTURE_H
#define FIXTURE_H

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

#endif
