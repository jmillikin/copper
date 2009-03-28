/* String.cpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006-2009 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper/String.hpp>

#include <cassert>
#include <cstdarg>
#include <cstring>

using std::size_t;
using std::strcmp;
using std::strlen;
using std::strncpy;

namespace {

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
COPPER_FUNCATTR_MALLOC
copper_strndup (const char *string, const size_t size)
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

char *
copper_strpcpy (char *dest, const char *src)
{
	while ((*dest++ = *src++)) {}
	return dest - 1;
}

}

namespace Copper {

class String::Impl
{
public:
	Impl (const char *str, size_t size, bool should_delete)
	: str (str), size (size), should_delete (should_delete),
	  references (1u)
	{}
	
	const char *str;
	size_t size;
	const bool should_delete;
	
	static Impl *
	Empty ()
	{
		static Impl empty ("", 0u, false);
		return &empty;
	}
	
	Impl *
	IncRef ()
	{
		++references;
		return this;
	}
	
	void
	DecRef ()
	{
		if (--references == 0u) { delete this; }
	}
	
private:
	unsigned int references;
	
	~Impl ()
	{
		if (should_delete) {
			assert (references == 0u);
			delete[] str;
		}
	}
};

/** @class String
 * @brief Immutable string class.
 * 
 * This is a simple String class to have some of the benefits of
 * RAII without having to depend on std::string.
 */

/**
 * @brief Construct an empty string
 */
String::String ()
: p (Impl::Empty ()->IncRef ())
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
                const size_t size)
{
	p = string[0]
		? new Impl (copper_strndup (string, size), 0u, true)
		: Impl::Empty ()->IncRef ();
}

String::String (const String &other)
: p (other.p->IncRef ())
{
}

String::~String ()
{
	p->DecRef ();
}

String &
String::operator= (const String &other)
{
	if (this != &other)
	{
		p->DecRef ();
		p = other.p->IncRef ();
	}
	
	return *this;
}

bool
String::operator== (const String &second) const
{
	if (p == second.p) { return true; }
	
	return (Size () == second.Size () &&
	        strcmp (CStr (), second.CStr ()) == 0);
}

bool
String::operator!= (const String &second) const
{
	return !(operator== (second));
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
String::FromStatic (const char string[])
{
	String new_string;
	new_string.p->DecRef ();
	new_string.p = new Impl (string, 0u, false);
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
String::NoCopy (const char *string)
{
	String new_string;
	new_string.p->DecRef ();
	new_string.p = new Impl (string, 0u, false);
	return new_string;
}

/**
 * @brief Builds a string from several character arrays.
 * 
 * Concatenates all the character arrays into one string, and
 * returns it.
 * 
 * @param first The first character array.
 * @param ... The remaining character arrays.
 * 
 * @return a string containing all the arrays, concatenated
 *         together.
 */
String
String::Build (const char *first, ...)
{
	va_list args;
	size_t size;
	char *new_c_str, *part, *ii;
	
	assert (first != NULL);
	
	/* Find the total size */
	size = strlen (first);
	va_start (args, first);
	while ((part = va_arg (args, char *)))
	{
		size += strlen (part);
	}
	va_end (args);
	
	/* Build the new string */
	ii = new_c_str = new char[size + 1];
	ii = copper_strpcpy (ii, first);
	va_start (args, first);
	while ((part = va_arg (args, char *)))
	{
		ii = copper_strpcpy (ii, part);
	}
	
	*ii = 0;
	
	String new_str;
	new_str.p->DecRef ();
	new_str.p = new Impl (new_c_str, size, true);
	return new_str;
}

/**
 * @brief Get the size of the string.
 * 
 * @return the size of this string, in bytes.
 */
size_t
String::Size () const
{
	if (!p->size)
		// I know this is evil, but it allows size to be
		// calculated only for strings that need it.
		p->size = strlen (p->str);
	return p->size;
}

/**
 * @brief Get a char * representation of this string.
 * 
 * @return a char * representation of this string.
 */
const char *
String::CStr () const
{
	return p->str;
}

}
