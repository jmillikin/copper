/* exception_protector.cpp -- Guards against unexpected exceptions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <stdexcept>

#include "../compat.hpp"
#include "exception_protector.hpp"
#include "../safe_exception.hpp"

#if HAVE_CXA_CURRENT_EXCEPTION_TYPE
#	include <cxxabi.h>
#endif

namespace Copper
{
	static
	String
	demangle (const char *name);

	/** @class ExceptionProtector
	 * @brief Guards against unknown exceptions being thrown by tests.
	 */

	/**
	 * @brief Default constructor
	 */
	ExceptionProtector::ExceptionProtector () throw ():
	                                        Protector ()
	{
	}

	/**
	 * @brief Default destructor
	 */
	ExceptionProtector::~ExceptionProtector () throw ()
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
	ExceptionProtector::_guard (Test *test)
	{
#	if !HAVE_EXCEPTIONS
		return next_protector (test, error);
#	else
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
			return new Error (String::build (2,
			                                 "Unhandled exception: ",
			                                 e.what ()));
		}

		catch (...)
		{
#	if HAVE_CXA_CURRENT_EXCEPTION_TYPE
			std::type_info *info;
			info = __cxxabiv1::__cxa_current_exception_type ();

			/* Unhandled exception of type 'type' */
			String message = String::build (3,
			                                "Unhandled exception of type '",
			                                demangle (info->name ()).c_str (),
			                                "'");

			return new Error (message);
#	else
			return new Error (String::from_static ("Unhandled exception with unknown type"));
#	endif /* HAVE_CXA_CURRENT_EXCEPTION_TYPE */
		}
#	endif /* HAVE_EXCEPTIONS */
	}

	static
	String
	demangle (const char *name)
	{
		int demangle_status = -1;
		char *demangled_name = NULL;

#	if HAVE_CXA_DEMANGLE
		demangled_name = __cxxabiv1::__cxa_demangle (
			name, NULL, NULL,
		        &demangle_status);
#	endif /* HAVE_CXA_DEMANGLE */

		if (demangle_status == 0)
		{
			String type_name = demangled_name;
			free (demangled_name);
			return type_name;
		}

		else
		{
			/* De-mangling the name failed */
			return name;
		}
	}
}
