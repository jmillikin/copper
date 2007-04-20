/* string.cpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cassert>
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
	 * @brief A version of strdup that takes an optional size parameter.
	 * 
	 * @param string The source string to duplicate.
	 * @param size If > 0, only this many characters will be copied
	 *             from the source string.
	 * 
	 * @return a new character array, which must be deallocated with
	 *         delete[].
	 */
	char *
	strndup (const char *string, const size_t size) throw ()
	{
		size_t string_len;

		assert (string != NULL);
		string_len = strlen (string);

		if (size && size < string_len)
		{
			string_len = size;
		}

		char *new_str = new char [string_len + 1];
		strncpy (new_str, string, string_len);
		new_str[string_len] = 0;
		return new_str;
	}

	String::String (const char *_str, const size_t size) throw ():
	                priv (new StringPrivate (strndup (_str, size)))
	{
	}

	String::String (const String &other) throw ():
	                priv (new StringPrivate (strndup (other.priv->str)))
	{
	}

	String::~String () throw () {
		delete[] priv->str;
		delete priv;
	}

	const String &
	String::operator= (const String &other) throw ()
	{
		delete[] priv->str;
		priv->str = strndup (other.priv->str);
		return *this;
	}

	bool
	String::operator== (const String &other) const throw ()
	{
		return strcmp (priv->str, other.priv->str) == 0;
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
		delete[] new_c_str;

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

	String
	operator+ (const char *a, const String &b) throw ()
	{
		return String (a) + b;
	}

	bool
	operator==(const char *a, const String &b) throw ()
	{
		return strcmp (a, b.c_str ()) == 0;
	}
}
