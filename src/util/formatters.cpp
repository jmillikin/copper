#include <copper/util/formatters.hpp>
#include "../export.hpp"

namespace Copper {

#if HAVE_SSTREAM

#if HAVE_BOOLEAN
template<>
String format<bool>(const bool& v) throw () {
  return String(v ? "true" : "false");
}
#endif /* HAVE_BOOLEAN */

template<>
String format<char>(const char& v) throw () {
  if (v < ' ' || v > '~') {
    return String("");
  }

  char buffer[] = {v, '\0'};
  return String(buffer);
}

template<>
String format<String>(const String& v) throw () {
  return v;
}

#else

#if HAVE_BOOLEAN
EXPORT String format(const bool& v) throw () {
  return String(v ? "true" : "false");
}
#endif /* HAVE_BOOLEAN */

EXPORT String format(const char& v) throw () {
  if (v < ' ' || v > '~') {
    return String("");
  }

  char buffer[] = {v, '\0'};
  return String(buffer);
}

EXPORT String format(const signed char& v) throw () {
  return format(static_cast<char>(v));
}

EXPORT String format(const unsigned char& v) throw () {
  return format(static_cast<char>(v));
}

EXPORT String format(const signed short& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%hd", v);
  return String(buffer);
}

EXPORT String format(const unsigned short& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%hu", v);
  return String(buffer);
}

EXPORT String format(const signed int& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%d", v);
  return String(buffer);
}

EXPORT String format(const unsigned int& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%u", v);
  return String(buffer);
}

EXPORT String format(const signed long& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%ld", v);
  return String(buffer);
}

EXPORT String format(const unsigned long& v) throw () {
  char buffer[50];
  std::sprintf(buffer, "%lu", v);
  return String(buffer);
}

/* FIXME I'm pretty sure this will break for weird values */
EXPORT String format(const float& v) throw () {
  char buffer[100]; /* FIXME: enough? */
  std::sprintf(buffer, "%g", v);
  return String(buffer);
}

/* FIXME, see format(float) */
EXPORT String format(const double& v) throw () {
  return format(static_cast<float>(v));
}

EXPORT String format(const char* v) throw () {
  return String(v);
}

EXPORT String format(const String& v) throw () {
  return v;
}

#endif /* HAVE_SSTREAM */

} /* Namespace */
