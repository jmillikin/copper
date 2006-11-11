/* error.cpp - Created when an execution error occurs
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <cstring>
#include <cstdlib>
#include <copper/error.hpp>

namespace Copper {

Error::Error(const String& _message) throw ():
  message(_message) {}

Error::~Error() throw () {}

} // namespace
