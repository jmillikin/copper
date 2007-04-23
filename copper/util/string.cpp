/* string.cpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cassert>
#include <cstdarg>
#include <cstring>

#include "../compat.hpp"
#include "string.hpp"

using namespace std;

namespace Copper
{
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
	String::String () throw ():
	                str (""),
	                _size (0u),
	                should_delete (false)
	{
	}

	/**
	 * @brief Construct a new string.
	 * 
	 * @param string The source string to be stored.
	 * @param size If > 0, only this many bytes will be copied from
	 *             the source string.
	 */
	String::String (const char *string,
	                const std::size_t size) throw ():
	                str (""),
	                _size (0u),
	                should_delete (false)
	{
		if (string[0])
		{
			str = strndup (string, size);
			should_delete = true;
		}
	}

	/**
	 * @brief Copy an existing string.
	 * 
	 * @param other The string to copy.
	 */
	String::String (const String &other) throw ():
	                _size (other._size),
	                should_delete (other.should_delete)
	{
		if (should_delete)
			str = strndup (other.str);

		else
			str = other.str;
	}

	/**
	 * @brief Deallocate resources used by this string.
	 */
	String::~String () throw () {
		if (should_delete)
			delete[] str;
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
	String::from_static (const char string[]) throw ()
	{
		String new_string;
		new_string.str = const_cast<char *> (string);
		return new_string;
	}

	/**
	 * @brief Construct a new string without copying data.
	 * 
	 * This function is provided for performance reasons, to avoid
	 * copying character data if the data is guaranteed to exist for the
	 * lifetime of the String object.
	 * 
	 * @param string The data to store in this string.
	 */
	String
	String::no_copy (const char *string) throw ()
	{
		String new_string;
		new_string.str = const_cast<char *> (string);
		return new_string;
	}

	struct BuilderInfo
	{
		char *str;
		size_t len;
	};

	/**
	 * @brief Builds a string from several character arrays.
	 * 
	 * Concatenates all the character arrays into one string, and
	 * returns it.
	 * 
	 * @param count How many character arrays were passed.
	 * @param ... The character arrays to concatenate.
	 * 
	 * @return a string containing all the arrays, concatenated
	 *         together.
	 */
	String
	String::build (const std::size_t count, ...) throw ()
	{
		va_list args;
		va_start (args, count);
		size_t full_size = 0, ii, idx = 0;
		String new_str;
		BuilderInfo *strings = new BuilderInfo[count];
		char *new_c_str;

		/* Find the total size */
		for (ii = 0; ii < count; ii++)
		{
			strings[ii].str = va_arg (args, char *);
			strings[ii].len = strlen (strings[ii].str);
			full_size += strings[ii].len;
		}

		va_end (args);

		/* Build the new string */
		new_c_str = new char[full_size + 1];

		for (ii = 0; ii < count; ii++)
		{
			strcpy (new_c_str + idx, strings[ii].str);
			idx += strings[ii].len;
		}

		new_c_str[full_size] = 0;

		delete[] strings;

		new_str.str = new_c_str;
		new_str._size = full_size;
		new_str.should_delete = true;
		return new_str;
	}

	/**
	 * @brief Get the size of the string.
	 * 
	 * @return the size of this string, in bytes.
	 */
	size_t
	String::size () const throw ()
	{
		if (!_size)
			// I know this is evil, but it allows size to be
			// calculated only for strings that need it.
			const_cast<String *> (this)->_size = strlen (str);
		return _size;
	}

	/**
	 * @brief Get a char * representation of this string.
	 * 
	 * @return a char * representation of this string.
	 */
	const char *
	String::c_str () const throw ()
	{
		return str;
	}

	char *
	strjoin (const char *first, const char *second) throw ()
	{
		size_t first_size = strlen (first);
		size_t full_size = first_size + strlen (second);
		char *new_c_str = new char [full_size + 1];

		strcpy (new_c_str, first);
		strcpy (new_c_str + first_size, second);

		new_c_str[full_size] = 0;

		return new_c_str;
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
		return (first.size () == second.size ()) &&
		       (strcmp (first.c_str (), second.c_str ()) == 0);
	}
}
