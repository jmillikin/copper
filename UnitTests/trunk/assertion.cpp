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


std::string equal(char const*  result, char const*  expected) throw () {
  std::string s_result = result, s_expected = expected;
  return equal(s_result, s_expected);
}
