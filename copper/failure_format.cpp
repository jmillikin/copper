/* failure_format.hpp -- Pretty formatting of failure messages
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "failure_format.hpp"

namespace Copper {
	String
	failure_format(const char &v)
	{
		return String::build (3, "'", format (v).c_str (), "'");
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
		return String::build (3, "\"", v.c_str (), "\"");
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
			return failure_format (String::no_copy (v));
		else
			return String::from_static ("NULL");
	}

#if HAVE_STD_STRING
	String
	failure_format (const std::string &v)
	{
		return failure_format (v.c_str());
	}
#endif
}

