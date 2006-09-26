/* protector.h - Base class for all protectors
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef PROTECTOR_H
#define PROTECTOR_H

#include "error_exception.h"

// Disable warnings about throw specifications in VS 2003
#ifdef _MSC_VER
#pragma warning(disable: 4290)
#endif

namespace UnitTests {

class Test;
class Assertion;

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
  static Assertion* guard(Test* test);

protected:
  /**
    Call the next Protector in the global list to guard the test

    @param test The Test to guard
  */
  Assertion* next_protector(Test* test);

  /**
    Guard a test with this Protector. It is important that protectors be
    nested for them to work properly, so use next_protector() to do so

    @param test The Test to guard
  */
  virtual Assertion* _guard(Test* test) throw (ErrorException) = 0;
};

} // namespace

#endif /* PROTECTOR_H */
