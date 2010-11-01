/* String.hpp -- Simple string to avoid dependency on std::string
 * Copyright (C) 2006-2009 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_UTIL_STRING_HPP
#define COPPER_UTIL_STRING_HPP

#include <cstddef>
#include <copper/FuncAttrs.hpp>

namespace Copper {

class COPPER_FUNCATTR_EXPORT String
{
public:
	String ();
	
	String (const char *string,
	        const std::size_t size = 0);
	
	String (const String &other);
	
	~String ();
	
	String &
	operator= (const String &other);
	
	bool
	operator== (const String &other) const;
	
	bool
	operator!= (const String &other) const;
	
	static String
	FromStatic (const char string[]);
	
	static String
	NoCopy (const char *string);
	
	static String
	COPPER_FUNCATTR_NULL_TERMINATED
	Build (const char *first, ...);
	
	std::size_t
	Size () const;
	
	const char *
	CStr () const;
	
private:
	class Impl;
	Impl *p;
};

}

#endif
