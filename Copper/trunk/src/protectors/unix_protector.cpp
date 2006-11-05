/* unix_protector.cpp -- Guards against unexpected UNIX signals
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

// For strsignal
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <signal.h>
#include <setjmp.h>
#include <cstring>
#include <copper/protectors/unix_protector.hpp>

// Used in trap(), since nothing C++-like can be used
typedef Copper::UnixProtector c_UnixProtector;
typedef Copper::Test c_Test;
typedef Copper::Assertion c_Assertion;
typedef Copper::Error c_Error;

#if HAVE_SIGBUS
const unsigned int SIGNAL_COUNT = 3;
int signals[SIGNAL_COUNT] = {
  SIGSEGV,
  SIGFPE,
  SIGBUS
};
#else
const unsigned int SIGNAL_COUNT = 2;
int signals[SIGNAL_COUNT] = {
  SIGSEGV,
  SIGFPE
};
#endif

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

namespace Copper {

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
