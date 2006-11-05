/* string.cpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */


#include <cstdlib>
#include <cstring>
#include <copper/util/string.hpp>

namespace Copper {

String::String(const char* _str) throw(): str(strdup(_str)) {}

String::String(const String& other) throw(): str(strdup(other.str)) {}

String::~String() throw () {
  free(str);
}

const String& String::operator=(const String& other) throw () {
  free(str);
  str = strdup(other.str);
  return *this;
}

bool String::operator==(const String& other) const throw () {
  return strcmp(str, other.str) == 0;
}

bool operator==(const char* a, const String& b) throw () {
  return strcmp(a, b.c_str()) == 0;
}

String String::operator+(const String& other) const throw () {
  size_t this_size = size();
  char* new_c_str = static_cast<char*>(
    calloc(this_size + other.size() + 1, sizeof(char))
  );
  strcpy(new_c_str, str);
  strcpy(new_c_str + this_size, other.str);

  String new_str(new_c_str);
  free(new_c_str);

  return new_str;
}

size_t String::size() const throw () {
  return strlen(str);
}

const char* String::c_str() const throw () {
  return str;
}

} /* Namespace */
