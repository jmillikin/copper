/* string.cpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cstring>

#include "../compat.hpp"
#include "string.hpp"

using namespace std;

namespace Copper
{
	class StringPrivate
	{
	public:
		StringPrivate (char *str):
		               str(str)
		{
		}

		char *str;
	};

	/**
	 * An implementation of the GNU project's strndup
	 */
	char *
	strndup (const char *a, const unsigned int size) throw ()
	{
		size_t a_len = strlen (a);

		if (size && size < a_len)
		{
			a_len = size;
		}

		char *b = new char [a_len + 1];
		strncpy (b, a, a_len);
		b[a_len] = 0;
		return b;
	}

	String::String (const char *_str, const unsigned int size) throw ():
	                priv (new StringPrivate (strndup (_str, size)))
	{
	}

	String::String (const String &other) throw ():
	                priv (new StringPrivate (strndup (other.priv->str)))
	{
	}

	String::~String () throw () {
		delete priv->str;
		delete priv;
	}

	const String &
	String::operator= (const String &other) throw ()
	{
		delete priv->str;
		priv->str = strndup (other.priv->str);
		return *this;
	}

	bool
	String::operator== (const String &other) const throw ()
	{
		return strcmp (priv->str, other.priv->str) == 0;
	}

	bool
	operator==(const char *a, const String &b) throw ()
	{
		return strcmp (a, b.c_str ()) == 0;
	}

	String
	String::operator+ (const String &other) const throw ()
	{
		size_t this_size = size ();
		size_t full_size = this_size + other.size ();

		char *new_c_str = new char [full_size + 1];
		strcpy (new_c_str, priv->str);
		strcpy (new_c_str + this_size, other.priv->str);

		new_c_str[full_size] = 0;

		String new_str (new_c_str);
		delete new_c_str;

		return new_str;
	}

	size_t
	String::size () const throw ()
	{
		return strlen (priv->str);
	}

	const char *
	String::c_str () const throw ()
	{
		return priv->str;
	}

}
