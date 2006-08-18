#include "assertion.h"

#undef assert
#undef failed

void assert(const std::string& assertion, const bool result,
  const unsigned int line) throw (UnitTests::FailureException) {

  if (!result) {
    throw UnitTests::FailureException(assertion,
      "Boolean assertion failed", line);
  }
}

void assert(const std::string& assertion, const std::string& result,
  const unsigned int line) throw (UnitTests::FailureException) {

  if (result.size() > 0) {
    throw UnitTests::FailureException(assertion, result, line);
  }
}

std::string failed(const std::string& assertion,
  const std::string& result) throw () {

  if (result.size() > 0) {
    return "";
  }

  return "Unexpected sucess of assertion '" + assertion + "'";
}

std::string failed(const std::string& assertion, const bool result) throw () {
  if (!result) {
    return "";
  }

  return "Boolean assertion '" + assertion + "' succeeded";
}

std::string equal(const char* expected, const char* result) throw () {
  return equal<>((std::string)(expected), (std::string)(result));
}

std::string equal(const std::string& expected, const std::string& result) throw () {
  return equal<std::string>(expected, result);
}
