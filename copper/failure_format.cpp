/* failure_format.hpp -- Pretty formatting of failure messages
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "failure_format.hpp"

namespace Copper {
	String
	failure_format(const char &v) throw ()
	{
		return "'" + format (v) + "'";
	}

	String
	failure_format (const signed char &v) throw ()
	{
		return failure_format (static_cast<char>(v));
	}

	String
	failure_format (const unsigned char &v) throw ()
	{
		return failure_format (static_cast<char>(v));
	}

	String
	failure_format(const String &v) throw ()
	{
		return "\"" + v + "\"";
	}

	String
	failure_format (char *v) throw ()
	{
		return failure_format (static_cast <const char *> (v));
	}

	String
	failure_format (const char *v) throw ()
	{
		if (v)
			return failure_format (String (v));
		else
			return String ("NULL");
	}
}
