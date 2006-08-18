#ifndef LINUX_PROTECTOR_H
#define LINUX_PROTECTOR_H

#include "../protector.h"

namespace UnitTests {

/**
  Guard against things like segmentation faults or double-frees, using
  Linux-specific functions
*/
class LinuxProtector : public Protector {
public:
  /** Default constructor */
  LinuxProtector() throw ();

  /** Default destructor */
  ~LinuxProtector() throw ();

  /** Used by external guard_test */
  void guard_test(Test* test) throw (FailureException, ErrorException);

protected:
  /**
    Guard a test with this Protector, to ensure it doesn't terminate the
    test suite if something goes wrong

    @param test The test to guard
  */
  virtual void _guard(Test* test)
    throw (FailureException, ErrorException);
} linux_protector_instance;

} // namespace

#endif /* LINUX_PROTECTOR_H */
