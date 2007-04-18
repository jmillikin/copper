/* formatters.cpp -- Convert various types to Copper::String
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstdio>

#include <copper/util/formatters.hpp>
#include "../export.hpp"

namespace Copper {

#if HAVE_BOOLEAN
	COPPER_EXPORT
	String
	format(const bool &v) throw ()
	{
		return String (v ? "true" : "false");
	}
#endif /* HAVE_BOOLEAN */

	COPPER_EXPORT
	String
	format(const char &v) throw ()
	{
		if (v < ' ' || v > '~')
		{
			return String ("");
		}

		char buffer[] = {v, '\0'};
		return String (buffer);
	}

	COPPER_EXPORT
	String
	format (const signed char &v) throw ()
	{
		return format (static_cast<char>(v));
	}

	COPPER_EXPORT
	String
	format (const unsigned char &v) throw ()
	{
		return format (static_cast<char>(v));
	}

	COPPER_EXPORT
	String
	format(const String &v) throw ()
	{
		return v;
	}

	COPPER_EXPORT
	String
	format (const signed short &v) throw ()
	{
		char buffer[50];
		std::sprintf (buffer, "%hd", v);
		return String (buffer);
	}

	COPPER_EXPORT
	String
	format (const unsigned short &v) throw ()
	{
		char buffer[50];
		std::sprintf (buffer, "%hu", v);
		return String (buffer);
	}

	COPPER_EXPORT
	String
	format (const signed int &v) throw ()
	{
		char buffer[50];
		std::sprintf (buffer, "%d", v);
		return String (buffer);
	}

	COPPER_EXPORT
	String
	format (const unsigned int &v) throw ()
	{
		char buffer[50];
		std::sprintf (buffer, "%u", v);
		return String (buffer);
	}

	COPPER_EXPORT
	String
	format (const signed long &v) throw ()
	{
		char buffer[50];
		std::sprintf (buffer, "%ld", v);
		return String (buffer);
	}

	COPPER_EXPORT
	String
	format (const unsigned long &v) throw ()
	{
		char buffer[50];
		std::sprintf (buffer, "%lu", v);
		return String (buffer);
	}

	/* FIXME, see format (double) */
	COPPER_EXPORT
	String
	format (const float &v) throw ()
	{
		return format (static_cast<double>(v));
	}

	/* FIXME I'm pretty sure this will break for weird values */
	COPPER_EXPORT
	String
	format (const double &v) throw ()
	{
		char buffer[100]; /* FIXME: enough? */
		std::sprintf (buffer, "%g", v);
		return String (buffer);
	}

	COPPER_EXPORT
	String
	format (const char *v) throw ()
	{
		return String (v);
	}
}

