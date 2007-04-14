/* string.hpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_UTIL_STRING_HPP
#define COPPER_UTIL_STRING_HPP

#include <cstddef>

namespace Copper
{
	/**
	 * An implementation of the GNU project's strndup
	 */
	char *
	strndup (const char *a, const unsigned int size = 0) throw ();

	class String
	{
	public:
		String (const char *string = "",
		        const unsigned int size = 0) throw ();

		String (const String &other) throw ();

		~String () throw ();

		const String &
		operator=(const String &other) throw ();

		bool
		operator== (const String &other) const throw ();

		String
		operator+ (const String &other) const throw ();

		std::size_t
		size () const throw ();

		const char *
		c_str () const throw ();

	protected:
		char *str;
	};

	bool
	operator== (const char *a, const String &b) throw ();
}

#endif /* COPPER_UTIL_STRING_HPP */
