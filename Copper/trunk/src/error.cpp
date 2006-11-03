/* error.cpp - Created when an execution error occurs
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <cstring>
#include <cstdlib>
#include <copper/error.hpp>

namespace Copper {

Error::Error(const char* _message) throw ():
  message(strdup(_message)) {}

Error::~Error() throw () {
  free(const_cast<char*>(message));
}

} // namespace
