/* exception_protector.cpp -- Guards against unexpected exceptions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <stdexcept>
#include <copper/protectors/exception_protector.hpp>
#include <copper/compat.hpp>
#include <copper/safe_exception.hpp>

#if HAVE_CXA_CURRENT_EXCEPTION_TYPE
#	include <cxxabi.h>
#endif

namespace Copper
{
	ExceptionProtector::ExceptionProtector () throw ():
	                                        Protector ()
	{
	}

	ExceptionProtector::~ExceptionProtector () throw ()
	{
	}

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
			String message = "Unhandled exception: ";
			return new Error (message + e.what ());
		}

		catch (...)
		{
#	if HAVE_CXA_CURRENT_EXCEPTION_TYPE
			/* Unhandled exception of type 'type' */
			String message = "Unhandled exception of type ";

			std::type_info *info;
			info = __cxxabiv1::__cxa_current_exception_type ();

			int demangle_status = -1;
			char *demangled_name = NULL;

#	if HAVE_CXA_DEMANGLE
			demangled_name = __cxxabiv1::__cxa_demangle (
				info->name (), NULL, NULL, &demangle_status);
#	endif /* HAVE_CXA_DEMANGLE */

			String type_name;
			if (demangle_status == 0)
			{
				type_name = demangled_name;
				free (demangled_name);
			}

			else
			{
				/* De-mangling the name failed */
				type_name = info->name ();
			}

			message = message + "'" + type_name + "'";

			return new Error (message);
#	else
			return new Error ("Unhandled exception with unknown type");
#	endif /* HAVE_CXA_CURRENT_EXCEPTION_TYPE */
		}
#	endif /* HAVE_EXCEPTIONS */
	}
}
