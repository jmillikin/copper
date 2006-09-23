#ifndef ERROR_EXCEPTION_H
#define ERROR_EXCEPTION_H

#include <string>

namespace UnitTests {

/**
  This is used to indicate that something unexpected went wrong running a test
*/
class ErrorException {
public:
  /**
    Default constructor

    @param message The error string
  */
  ErrorException(const std::string& message) throw ();

  /** Default constructor */
  ~ErrorException() throw ();

  /** The error that occurred */
  const char* message;
};

} // namespace

#endif /* ERROR_EXCEPTION_H */
