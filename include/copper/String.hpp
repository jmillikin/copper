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
	String(const String &other);
	
	~String();
	
	bool operator==(const String &other) const;
	bool operator==(const char *other) const;
	
	bool operator!=(const String &other) const;
	bool operator!=(const char *other) const;
	
	String &operator=(const String &other);
	
	static String peek(const char *string);
	static String copy(const char *string);
	static String copy(const char *string, std::size_t size);
	static String steal(char *string);
	static String steal(char *string, std::size_t size);
	
	COPPER_FUNCATTR_NULL_TERMINATED
	static String build(const char *first, ...);
	
	std::size_t size() const;
	
	const char *c_str() const;
	
private:
	class Impl;
	String(Impl *p);
	Impl *p;
};

}

#endif
