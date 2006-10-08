/* error_exception.cpp - Thrown when an error occurs
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "error_exception.hpp"
#include <cstring>
#include <cstdlib>

namespace UnitTests {

ErrorException::ErrorException(const char* _message) throw ():
  message(strdup(_message)) {}

ErrorException::~ErrorException() throw () {
  free(const_cast<char*>(message));
}

} // namespace
