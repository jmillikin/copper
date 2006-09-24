/* error_exception.cpp - Thrown when an error occurs
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include "error_exception.h"

namespace UnitTests {

ErrorException::ErrorException(const std::string& _message) throw ():
  message(strdup(_message.c_str())) {}

ErrorException::~ErrorException() throw () {
  free(const_cast<char*>(message));
}

} // namespace
