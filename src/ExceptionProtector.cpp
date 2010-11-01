/* ExceptionProtector.cpp -- Guards against unexpected exceptions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <stdexcept>
#include <cstdlib>

#include <copper/config.h>
#include <copper/ExceptionProtector.hpp>
#include <copper/SafeException.hpp>
#include <copper/String.hpp>

#if HAVE_CXA_CURRENT_EXCEPTION_TYPE
#	include <cxxabi.h>
#endif

using Copper::String;

namespace {

String
demangle (const char *name)
{
	int demangle_status = -1;
	char *demangled_name = NULL;
	
#if HAVE_CXA_DEMANGLE
	demangled_name = ::abi::__cxa_demangle (
		name, NULL, NULL,
		&demangle_status);
#endif
	
	if (demangle_status == 0)
	{
		String type_name = demangled_name;
		free (demangled_name);
		return type_name;
	}
	
	/* De-mangling the name failed */
	return name;
}

}

namespace Copper {

/** @class ExceptionProtector
 * @brief Guards against unknown exceptions being thrown by tests.
 */

/**
 * @brief Default constructor
 */
ExceptionProtector::ExceptionProtector ()
: Protector ()
{
}

/**
 * @brief Default destructor
 */
ExceptionProtector::~ExceptionProtector ()
{
}

/**
 * @brief Guard a test with this Protector, to ensure it doesn't
 * throw any weird exceptions.
 * 
 * @param test The Test to guard.
 * 
 * @return If an error occurred, a pointer to the error
 *         description. If no error occurred, returns NULL.
*/
Error *
ExceptionProtector::_guard (Test &test)
{
	try
	{
		return next_protector (test);
	}
	
	catch (const SafeException &)
	{
		/* Allow Copper exceptions to pass through */
		throw;
	}
	
	catch (const std::exception &e)
	{
		return new Error (String::Build ("Unhandled exception: ",
		                                 e.what (), NULL));
	}
	
	catch (...)
	{
#if HAVE_CXA_CURRENT_EXCEPTION_TYPE
		std::type_info *info;
		info = ::abi::__cxa_current_exception_type ();
		
		/* Unhandled exception of type 'type' */
		String message = String::Build ("Unhandled exception of type '",
		                                demangle (info->name ()).CStr (),
		                                "'", NULL);
		
		return new Error (message);
#else
		return new Error (String::FromStatic ("Unhandled exception with unknown type"));
#endif
	}
}

}
