#ifndef PROTECTOR_H
#define PROTECTOR_H

#include "failure_exception.h"
#include "error_exception.h"

namespace UnitTests {

class Test;

/**
  Protectors guard against possible errors while running a test. This is an
  abstract interface for a Protector, which must be subclassed to be useful
*/
class Protector {
public:
  /** Default constructor */
  Protector() throw ();

  /** Default destructor */
  virtual ~Protector() throw ();

  /**
    Add a protector to the list of available protectors

    @param protector The Protector to add
  */
  static void add(Protector* protector);

  /**
    Guard a test with all protectors currently available

    @param test The Test to guard
  */
  static void guard(Test* test);

protected:
  /**
    Call the next Protector in the global list to guard the test

    @param test The Test to guard
  */
  void next_protector(Test* test);

  /**
    Guard a test with this Protector. It is important that protectors be
    nested for them to work properly, so use next_protector() to do so

    @param test The Test to guard
  */
  virtual void _guard(Test* test) throw (FailureException, ErrorException) = 0;
};

} // namespace

#endif /* PROTECTOR_H */
