/* string.hpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_UTIL_STRING_HPP
#define COPPER_UTIL_STRING_HPP

#include <cstddef>

#include <copper/export.hpp>

namespace Copper
{
	COPPER_EXPORT
	char *
	strndup (const char *string, const std::size_t size = 0) throw ();

	class COPPER_EXPORT String
	{
	public:
		String () throw ();

		String (const char *string,
		        const std::size_t size = 0) throw ();

		String (const String &other) throw ();

		~String () throw ();

		static
		String
		from_static (const char string[]) throw ();

		static
		String
		no_copy (const char *string) throw ();

		static
		String
		build (const std::size_t count, ...) throw ();

		const String &
		operator=(const String &other) throw ();

		std::size_t
		size () const throw ();

		const char *
		c_str () const throw ();

	private:
		char *str;
		bool should_delete;
	};

	COPPER_EXPORT
	bool
	operator== (const String &first, const String &second) throw ();
}

#endif /* COPPER_UTIL_STRING_HPP */
