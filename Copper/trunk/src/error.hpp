/* error.hpp - Created when an execution error occurs
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#ifndef ERROR_HPP
#define ERROR_HPP

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
  Error(const char* message) throw ();

  /** Default constructor */
  ~Error() throw ();

  /** The error that occurred */
  const char* message;
};

} // namespace

#endif /* ERROR_HPP */
