/* unix_protector.cpp -- Guards against unexpected UNIX signals
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <signal.h>
#include <setjmp.h>
#include <cstring>
#include "unix_protector.hpp"

// Used in trap(), since nothing C++-like can be used
typedef UnitTests::UnixProtector c_UnixProtector;
typedef UnitTests::Test c_Test;
typedef UnitTests::Assertion c_Assertion;
typedef UnitTests::Error c_Error;

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

c_Error* new_Error(const char* str) {
  return new c_Error(str);
}

/**
  This function traps signals, and sends them to throw_error() for conversion
  into an exception
*/
void trap(
  c_UnixProtector* protector,
  c_Test* test,
  c_Assertion** failure,
  c_Error** error) {

  int sig;
  unsigned int ii;

  for (ii = 0; ii < SIGNAL_COUNT; ii++) {
    signal(signals[ii], handler);
  }

  sig = setjmp(jb);
  if (sig) {
    *error = new_Error(strsignal(sig));
  }

  else {
    protector->guard_test(test, failure, error);
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

void UnixProtector::_guard(Test* test, Assertion** failure,
  Error** error) {

  trap(this, test, failure, error);
}

void UnixProtector::guard_test(Test* test, Assertion** failure,
  Error** error) {

  next_protector(test, failure, error);
}

} // namespace
