#ifndef FAILURE_EXCEPTION_H
#define FAILURE_EXCEPTION_H

#include <string>

namespace UnitTests {

class FailureException {
public:
  /**
    Default constructor

    @param assertion The assertion that failed
    @param message The error string from the assertion
    @param line Which line of source code the assertion is at
  */
  FailureException(
    const std::string& assertion,
    const std::string& message,
    const unsigned int line) throw ();

  /** Default constructor */
  ~FailureException() throw ();

  /** The assertion that failed */
  const char* assertion;

  /** The error string from the assertion */
  const char* message;

  /** Which line of source code the assertion is at */
  const unsigned int line;
};

} // namespace

#endif // FAILURE_EXCEPTION_H
