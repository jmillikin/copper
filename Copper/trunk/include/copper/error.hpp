/* error.hpp - Created when an execution error occurs
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef COPPER_ERROR_HPP
#define COPPER_ERROR_HPP

#include <copper/util/string.hpp>

namespace Copper {

/**
  This is used to indicate that something unexpected went wrong running a test
*/
class Error {
public:
  /**
    Default constructor

    @param message The error string
  */
  Error(const String& message) throw ();

  /** Default constructor */
  ~Error() throw ();

  /** The error that occurred */
  const String message;
};

} // namespace

#endif /* COPPER_ERROR_HPP */
