/* exception_protector.cpp -- Guards against unexpected exceptions
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see license.txt
 */

#include <stdexcept>
#include <copper/protectors/exception_protector.hpp>
#include "../export.hpp"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if HAVE_CXA_CURRENT_EXCEPTION_TYPE
#include <cxxabi.h>
#endif

namespace Copper {

EXPORT ExceptionProtector::ExceptionProtector() throw ():
  Protector() {}

EXPORT ExceptionProtector::~ExceptionProtector() throw () {}

void ExceptionProtector::_guard(Test* test, Assertion** failure,
  Error** error) {

#if !HAVE_EXCEPTIONS
  next_protector(test, failure, error);
#else
  try {
    next_protector(test, failure, error);
  }

  catch (const std::exception& e){
    String message = "Unhandled exception: ";
    *error = new Error(message + e.what());
  }

  catch (...){
#if HAVE_CXA_CURRENT_EXCEPTION_TYPE
    /* Unhandled exception of type 'type' */
    String message = "Unhandled exception of type ";

    std::type_info* info = __cxxabiv1::__cxa_current_exception_type();

    int demangle_status = -1;
    char* demangled_name = NULL;

#if HAVE_CXA_DEMANGLE
    demangled_name = __cxxabiv1::__cxa_demangle(
      info->name(), NULL, NULL, &demangle_status);
#endif /* HAVE_CXA_DEMANGLE */

    String type_name;
    if (demangle_status == 0) {
      type_name = demangled_name;
      free(demangled_name);
    }

    else {
      /* De-mangling the name failed, use the mangled name */
      type_name = info->name();
    }

    message = message + "'" + type_name + "'";

    *error = new Error(message);
#else
    *error = new Error("Unhandled exception with unknown type");
#endif /* HAVE_CXA_CURRENT_EXCEPTION_TYPE */
  }
#endif /* HAVE_EXCEPTIONS */
}

} // namespace
