#ifndef FAILURE_EXCEPTION_H
#define FAILURE_EXCEPTION_H

#include <string>

namespace UnitTests {

class FailureException {
public:
  FailureException(const std::string& message) throw ();
  ~FailureException() throw ();

  const std::string& get_message() const throw ();

protected:
  const std::string message;
};

} // namespace

#endif // FAILURE_EXCEPTION_H
