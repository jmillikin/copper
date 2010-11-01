/* failure_format.hpp -- Pretty formatting of failure messages
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/FailureFormat.hpp>

namespace Copper {
	String
	failure_format(const char &v)
	{
		return String::Build ("'", format (v).CStr (), "'", NULL);
	}

	String
	failure_format (const signed char &v)
	{
		return failure_format (static_cast<char>(v));
	}

	String
	failure_format (const unsigned char &v)
	{
		return failure_format (static_cast<char>(v));
	}

	String
	failure_format(const String &v)
	{
		return String::Build ("\"", v.CStr (), "\"", NULL);
	}

	String
	failure_format (char *v)
	{
		return failure_format (static_cast <const char *> (v));
	}

	String
	failure_format (const char *v)
	{
		if (v)
			return failure_format (String::NoCopy (v));
		else
			return String::FromStatic ("NULL");
	}

#if HAVE_STD_STRING
	String
	failure_format (const std::string &v)
	{
		return failure_format (v.c_str ());
	}
#endif
}

