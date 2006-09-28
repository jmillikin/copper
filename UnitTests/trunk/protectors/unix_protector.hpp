/* unix_protector.hpp -- Guards against unexpected UNIX signals
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef UNIX_PROTECTOR_HPP
#define UNIX_PROTECTOR_HPP

#include "../protector.hpp"

namespace UnitTests {

/**
  Guard against things like segmentation faults or double-frees, using
  Unix-specific functions
*/
class UnixProtector : public Protector {
public:
  /** Default constructor */
  UnixProtector() throw ();

  /** Default destructor */
  ~UnixProtector() throw ();

  /** Used by external guard_test */
  Assertion* guard_test(Test* test) throw (ErrorException);

protected:
  /**
    Guard a test with this Protector, to ensure it doesn't terminate the
    test suite if something goes wrong

    @param test The test to guard
  */
  virtual Assertion* _guard(Test* test) throw (ErrorException);
} unix_protector_instance;

} // namespace

#endif /* UNIX_PROTECTOR_HPP */
