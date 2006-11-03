/* protector.hpp - Base class for all protectors
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef PROTECTOR_HPP
#define PROTECTOR_HPP

// Disable warnings about throw specifications in VS 2003
#ifdef _MSC_VER
#pragma warning(disable: 4290)
#endif

#include "error.hpp"

namespace Copper {

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
    @param failure If the test failed, this will be changed to the
      assertion that caused the test to fail
    @param error If a protector caught an error, this will be changed to
      the error that was caught
  */
  static void guard(Test* test, Assertion** failure, Error** error);

protected:
  /**
    Call the next Protector in the global list to guard the test

    @param test The Test to guard

    @param failure If the test failed, this will be changed to the
      assertion that caused the test to fail
    @param error If a protector caught an error, this will be changed to
      the error that was caught
  */
  void next_protector(Test* test, Assertion** failure, Error** error);

  /**
    Guard a test with this Protector. It is important that protectors be
    nested for them to work properly, so use next_protector() to do so

    @param test The Test to guard

    @param failure If the test failed, this will be changed to the
      assertion that caused the test to fail
    @param error If a protector caught an error, this will be changed to
      the error that was caught
  */
  virtual void _guard(Test* test, Assertion** failure, Error** error) = 0;
};

} // namespace

#endif /* PROTECTOR_HPP */
