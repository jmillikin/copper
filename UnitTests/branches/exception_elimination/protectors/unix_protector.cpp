/* unix_protector.cpp -- Guards against unexpected UNIX signals
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <signal.h>
#include <setjmp.h>
#include "unix_protector.h"
#include "../assertion.h"

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
UnitTests::Assertion* guard_test(void* protector, void* test) {
  return reinterpret_cast<UnitTests::UnixProtector*>(protector)->guard_test(
    reinterpret_cast<UnitTests::Test*>(test));
}

/**
  This function traps signals, and sends them to throw_error() for conversion
  into an exception
*/
UnitTests::Assertion* trap(void* protector, void* test) {
  int sig;
  unsigned int ii;

  for (ii = 0; ii < SIGNAL_COUNT; ii++) {
    signal(signals[ii], handler);
  }

  sig = setjmp(jb);
  if (sig) {
    throw_error(sig);
    return 0;
  }

  else {
    UnitTests::Assertion* result = guard_test(protector, test);
    for (ii = 0; ii < SIGNAL_COUNT; ii++) {
      signal(signals[ii], SIG_DFL);
    }
    return result;
  }
}

namespace UnitTests {

UnixProtector::UnixProtector() throw ():
  Protector() {

  add(this);
}

UnixProtector::~UnixProtector() throw () {}

Assertion* UnixProtector::_guard(Test* test)
  throw (ErrorException) {

  return trap(this, test);
}

Assertion* UnixProtector::guard_test(Test* test)
  throw (ErrorException) {

  return next_protector(test);
}

} // namespace
