/* string.hpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_UTIL_STRING_HPP
#define COPPER_UTIL_STRING_HPP

#include <cstddef>
#include <copper/FuncAttrs.hpp>

namespace Copper
{
	COPPER_FUNCATTR_EXPORT
	char *
	strndup (const char *string, const std::size_t size = 0);

	class COPPER_FUNCATTR_EXPORT String
	{
	public:
		String ();

		String (const char *string,
		        const std::size_t size = 0);

		String (const String &other);

		~String ();

		static
		String
		from_static (const char string[]);

		static
		String
		no_copy (const char *string);

		static
		String
		build (const std::size_t count, ...);

		std::size_t
		size () const;

		const char *
		c_str () const;

	private:
		const String &
		operator= (const String &other);

		const char *str;
		mutable std::size_t _size;
		bool should_delete;
	};

	COPPER_FUNCATTR_EXPORT
	bool
	operator== (const String &first, const String &second);
}

#endif /* COPPER_UTIL_STRING_HPP */
