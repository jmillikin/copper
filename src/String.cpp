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

#include <copper/String.hpp>

#include <cassert>
#include <cstdarg>
#include <cstring>

using std::size_t;
using std::strcmp;
using std::strlen;
using std::strncpy;

#if __GNUC__ > 3
#	define COPPER_FUNCATTR_MALLOC __attribute__((__malloc__))
#else
#	define COPPER_FUNCATTR_MALLOC
#endif

COPPER_FUNCATTR_MALLOC
static char *copper_strndup(const char *string, const size_t size)
{
	size_t string_len;
	
	assert(string != NULL);
	string_len = strlen(string);
	
	if (size && size < string_len)
	{
		string_len = size;
	}
	
	char *new_str = new char [string_len + 1];
	strncpy(new_str, string, string_len);
	new_str[string_len] = 0;
	return new_str;
}

static char *copper_strpcpy(char *dest, const char *src)
{
	while ((*dest++ = *src++)) {}
	return dest - 1;
}

namespace Copper
{

class String::Impl
{
public:
	Impl(const char *str, size_t size, bool have_size, bool should_delete)
	: str(str)
	, size(size)
	, have_size(have_size)
	, should_delete(should_delete)
	, references(1u)
	{}
	
	const char *str;
	size_t size;
	bool have_size;
	const bool should_delete;
	
	static Impl *Empty()
	{
		static Impl empty("", 0u, true, false);
		return &empty;
	}
	
	Impl *IncRef()
	{
		++references;
		return this;
	}
	
	void DecRef()
	{
		if (--references == 0u) { delete this; }
	}
	
private:
	unsigned int references;
	
	~Impl()
	{
		if (should_delete) {
			assert(references == 0u);
			delete[] str;
		}
	}
};

String::String()
: p(Impl::Empty()->IncRef())
{
}

String::String(const char *string, const size_t size)
{
	p = string[0]
		? new Impl(copper_strndup(string, size), 0u, false, true)
		: Impl::Empty()->IncRef();
}

String::String(const String &other)
: p(other.p->IncRef())
{
}

String::~String()
{
	p->DecRef();
}

String &String::operator=(const String &other)
{
	if (this != &other)
	{
		p->DecRef();
		p = other.p->IncRef();
	}
	
	return *this;
}

bool String::operator==(const String &second) const
{
	if (p == second.p) { return true; }
	
	return (Size() == second.Size() &&
	        strcmp(CStr(), second.CStr()) == 0);
}

bool String::operator!=(const String &second) const
{
	return !(operator==(second));
}

String String::FromStatic(const char string[])
{
	String new_string;
	new_string.p->DecRef();
	new_string.p = new Impl(string, 0u, false, false);
	return new_string;
}

String String::NoCopy(const char *string)
{
	String new_string;
	new_string.p->DecRef();
	new_string.p = new Impl(string, 0u, false, false);
	return new_string;
}

String
String::Build(const char *first, ...)
{
	va_list args;
	size_t size;
	char *new_c_str, *part, *ii;
	
	assert(first != NULL);
	
	/* Find the total size */
	size = strlen(first);
	va_start(args, first);
	while ((part = va_arg(args, char *)))
	{
		size += strlen(part);
	}
	va_end(args);
	
	/* Build the new string */
	ii = new_c_str = new char[size + 1];
	ii = copper_strpcpy(ii, first);
	va_start(args, first);
	while ((part = va_arg(args, char *)))
	{
		ii = copper_strpcpy(ii, part);
	}
	
	*ii = 0;
	
	String new_str;
	new_str.p->DecRef();
	new_str.p = new Impl(new_c_str, size, true, true);
	return new_str;
}

size_t String::Size() const
{
	if (!p->have_size)
	{
		p->size = strlen(p->str);
		p->have_size = true;
	}
	
	return p->size;
}

const char *String::CStr() const
{
	return p->str;
}

}
