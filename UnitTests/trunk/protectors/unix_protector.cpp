#include <signal.h>
#include <setjmp.h>
#include "unix_protector.h"

const unsigned int SIGNAL_COUNT = 3;
int signals[SIGNAL_COUNT] = {
  SIGSEGV,
  SIGFPE,
  SIGBUS
};

jmp_buf jb;

/** Small signal handler */
void handler(int sig) {
  longjmp(jb, sig);
}

/** Translates a signal into an exception, and then throws it */
void throw_error(int sig) throw (UnitTests::ErrorException) {
  throw UnitTests::ErrorException(strsignal(sig));
}

/**
  Small function for running the test, since trap() can't do anything
  C++
*/
void guard_test(void* protector, void* test) {
  reinterpret_cast<UnitTests::UnixProtector*>(protector)->guard_test(
    reinterpret_cast<UnitTests::Test*>(test));
}

/**
  This function traps signals, and sends them to throw_error() for conversion
  into an exception
*/
void trap(void* protector, void* test) {
  int sig;
  unsigned int ii;

  for (ii = 0; ii < SIGNAL_COUNT; ii++) {
    signal(signals[ii], handler);
  }

  sig = setjmp(jb);
  if (sig) {
    throw_error(sig);
  }

  else {
    guard_test(protector, test);
    for (ii = 0; ii < SIGNAL_COUNT; ii++) {
      signal(signals[ii], SIG_DFL);
    }
  }
}

namespace UnitTests {

UnixProtector::UnixProtector() throw ():
  Protector() {

  add(this);
}

UnixProtector::~UnixProtector() throw () {}

void UnixProtector::_guard(Test* test)
  throw (FailureException, ErrorException) {

  trap(this, test);
}

void UnixProtector::guard_test(Test* test)
  throw (FailureException, ErrorException) {

  next_protector(test);
}

} // namespace
