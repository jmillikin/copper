#include <cstdlib>
#include <cstring>
#include <copper/util/string.hpp>

namespace Copper {

String::String(const char* _str) throw(): str(strdup(_str)) {}

String::String(const String& b) throw(): str(strdup(other.str)) {}

String::~String() {
  free(str);
}

String& String::operator=(const String& other) const throw () {
  free(str);
  str = strdup(other.str);
}

bool String::operator==(const String& other) const throw () {
  return strcmp(str, other.str) == 0;
}

String String::operator+(const String& other) const throw () {
  size_t this_size = size();
  char* new_str = calloc(this_size + other.size() + 1);
  strcpy(new_str, str);
  strcpy(new_str + this_size, other.str);
  free(str);
  str = new_str;
}

size_t String::size() const throw () {
  return strlen(str);
}

const char* String::c_str() const throw () {
  return str;
}

} /* Namespace */
