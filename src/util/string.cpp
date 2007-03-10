/* string.cpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */


#include <cstdlib>
#include <cstring>
#include <copper/util/string.hpp>
#include <copper/compat.hpp>

namespace Copper {

char* strdup(const char* a) throw () {
  char* b = static_cast<char*>(std::calloc(std::strlen(a) + 1, sizeof(char)));
  std::strcpy(b, a);
  return b;
}

String::String(const char* _str) throw(): str(strdup(_str)) {}

String::String(const String& other) throw(): str(strdup(other.str)) {}

String::~String() throw () {
  std::free(str);
}

const String& String::operator=(const String& other) throw () {
  std::free(str);
  str = strdup(other.str);
  return *this;
}

bool String::operator==(const String& other) const throw () {
  return std::strcmp(str, other.str) == 0;
}

bool operator==(const char* a, const String& b) throw () {
  return std::strcmp(a, b.c_str()) == 0;
}

String String::operator+(const String& other) const throw () {
  std::size_t this_size = size();
  char* new_c_str = static_cast<char*>(
    std::calloc(this_size + other.size() + 1, sizeof(char))
  );
  std::strcpy(new_c_str, str);
  std::strcpy(new_c_str + this_size, other.str);

  String new_str(new_c_str);
  std::free(new_c_str);

  return new_str;
}

std::size_t String::size() const throw () {
  return std::strlen(str);
}

const char* String::c_str() const throw () {
  return str;
}

} /* Namespace */
