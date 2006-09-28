/* exception_protector.hpp -- Guards against unexpected exceptions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef EXCEPTION_PROTECTOR_HPP
#define EXCEPTION_PROTECTOR_HPP

#include "../protector.hpp"

namespace UnitTests {

/**
  Guard against unknown exceptions being thrown by tests. This isn't added by
  default, to allow tracing of thrown exceptions with a commandline option
*/
class ExceptionProtector : public Protector {
public:
  /** Default constructor */
  ExceptionProtector() throw ();

  /** Default destructor */
  ~ExceptionProtector() throw ();

protected:
  /**
    Guard a test with this Protector, to ensure it doesn't throw any weird
    exceptions

    @param test The test to guard
  */
  virtual Assertion* _guard(Test* test)
    throw (ErrorException);
};

} // namespace

#endif /* EXCEPTION_PROTECTOR_HPP */
