#ifndef EXCEPTION_PROTECTOR_H
#define EXCEPTION_PROTECTOR_H

#include "../protector.h"

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
  virtual void _guard(Test* test)
    throw (FailureException, ErrorException);
};

} // namespace

#endif /* EXCEPTION_PROTECTOR_H */