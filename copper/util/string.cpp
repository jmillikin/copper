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
		StringPrivate (char *str, bool should_delete):
		               str(str),
		               should_delete (should_delete)
		{
		}

		char *str;
		bool should_delete;
	};

	/**
	 * @brief A version of strdup that takes an optional size
	 *        parameter.
	 * 
	 * @param string The source string to duplicate.
	 * @param size If > 0, only this many bytes will be copied from
	 *             the source string.
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

	/**
	 * @brief Construct an empty string
	 */
	String::String () throw ()
	{
		priv = new StringPrivate ("", false);
	}

	/**
	 * @brief Construct a new string.
	 * 
	 * @param string The source string to be stored.
	 * @param size If > 0, only this many bytes will be copied from
	 *             the source string.
	 */
	String::String (const char *string,
	                const std::size_t size) throw ()
	{
		if (string[0])
			priv = new StringPrivate (strndup (string, size), true);
		else
			priv = new StringPrivate ("", false);
	}

	/**
	 * @brief Copy an existing string.
	 * 
	 * @param other The string to copy.
	 */
	String::String (const String &other) throw ()
	{
		if (other.priv->should_delete)
		{
			char *new_str = strndup (other.priv->str);
			priv = new StringPrivate (new_str, true);
		}
		else
			priv = new StringPrivate (other.priv->str, false);
	}

	/**
	 * @brief Deallocate resources used by this string.
	 */
	String::~String () throw () {
		if (priv->should_delete)
			delete[] priv->str;
		delete priv;
	}

	/**
	 * @brief Construct a new string from static data.
	 * 
	 * This function is provided for performance reasons, to avoid
	 * copying static character data.
	 * 
	 * @param string The static character data to store.
	 */
	String
	String::from_static (const char *string) throw ()
	{
		String new_string;
		new_string.priv->str = const_cast<char *> (string);
		return new_string;
	}

	/**
	 * @brief Copy another string over the contents of this string.
	 * 
	 * @param other The string to copy.
	 * 
	 * @return A reference to this string.
	 */
	const String &
	String::operator= (const String &other) throw ()
	{
		if (priv->should_delete)
			delete[] priv->str;

		priv->should_delete = other.priv->should_delete;
		if (other.priv->should_delete)
			priv->str = strndup (other.priv->str);
		else
			priv->str = other.priv->str;

		return *this;
	}

	/**
	 * @brief Get the size of the string.
	 * 
	 * @return the size of this string, in bytes.
	 */
	size_t
	String::size () const throw ()
	{
		return strlen (priv->str);
	}

	/**
	 * @brief Get a char * representation of this string.
	 * 
	 * @return a char * representation of this string.
	 */
	const char *
	String::c_str () const throw ()
	{
		return priv->str;
	}

	char *
	strjoin (const char *first, const char *second) throw ()
	{
		printf ("  Joining \"%s\" and \"%s\"\n", first, second);

		size_t first_size = strlen (first);
		size_t full_size = first_size + strlen (second);
		char *new_c_str = new char [full_size + 1];

		strcpy (new_c_str, first);
		strcpy (new_c_str + first_size, second);

		new_c_str[full_size] = 0;

		return new_c_str;
	}

	/**
	 * @brief Concatenate two strings.
	 * 
	 * @param first The first part of the new string.
	 * @param second The second part of the new string.
	 * 
	 * @return The two strings, concatenated together.
	 */
	String
	operator+ (const String &first, const String &second) throw ()
	{
		String new_str;

		new_str.priv->str = strjoin (first.c_str (), second.c_str ());
		new_str.priv->should_delete = true;
		return new_str;
	}

	String
	operator+ (const char *first,
	           const String &second) throw ()
	{
		String new_str;

		new_str.priv->str = strjoin (first, second.c_str ());
		new_str.priv->should_delete = true;
		return new_str;
	}

	String
	operator+ (const String &first,
	           const char *second) throw ()
	{
		String new_str;

		new_str.priv->str = strjoin (first.c_str (), second);
		new_str.priv->should_delete = true;
		return new_str;
	}

	/**
	 * @brief Compare two strings for equality.
	 * 
	 * @param first The first string to compare.
	 * @param second The second string to compare.
	 * 
	 * @return whether the strings are equal.
	 */
	bool
	operator== (const String &first, const String &second) throw ()
	{
		return strcmp (first.c_str (), second.c_str ()) == 0;
	}
}
