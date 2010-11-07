// Copyright (C) 2006-2010 John Millikin <jmillikin@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef COPPER_STRING_HPP
#define COPPER_STRING_HPP

#include <cstddef>

#if __GNUC__ >= 4
#	define COPPER_FUNCATTR_NULL_TERMINATED __attribute__((__sentinel__))
#else
#	define COPPER_FUNCATTR_NULL_TERMINATED
#endif

namespace Copper {

class String
{
public:
	String();
	String(const char *string, const std::size_t size = 0);
	String(const String &other);
	
	~String();
	
	String &operator=(const String &other);
	
	bool operator==(const String &other) const;
	bool operator!=(const String &other) const;
	
	static String FromStatic(const char string[]);
	
	static String NoCopy(const char *string);
	
	COPPER_FUNCATTR_NULL_TERMINATED
	static String Build(const char *first, ...);
	
	std::size_t Size() const;
	
	const char *CStr() const;
	
private:
	class Impl;
	Impl *p;
};

}

#endif
