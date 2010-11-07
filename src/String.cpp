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
static char *copper_strndup(const char *string, size_t size)
{
	size_t string_len;
	
	string_len = strlen(string);
	
	if (size && size < string_len)
	{
		string_len = size;
	}
	
	char *new_str = new char[string_len + 1];
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
	
	static Impl *empty()
	{
		static Impl empty("", 0u, true, false);
		return empty.ref();
	}
	
	Impl *ref()
	{
		++references;
		return this;
	}
	
	void unref()
	{
		if (--references == 0u) { delete this; }
	}
	
private:
	unsigned int references;
	
	~Impl()
	{
		if (should_delete) {
			delete[] str;
		}
	}
};

String::String()
: p(Impl::empty())
{
}

String::String(Impl *p)
: p(p)
{
}

String::String(const String &other)
: p(other.p->ref())
{
}

String::~String()
{
	p->unref();
}

String &String::operator=(const String &other)
{
	if (this != &other)
	{
		p->unref();
		p = other.p->ref();
	}
	
	return *this;
}

bool String::operator==(const String &other) const
{
	if (p == other.p) { return true; }
	
	return (size() == other.size() &&
	        strcmp(p->str, other.p->str) == 0);
}

bool String::operator==(const char *other) const
{
	if (p->str == other) { return true; }
	return (strcmp(p->str, other) == 0);
}

bool String::operator!=(const String &other) const
{
	return not (operator==(other));
}

bool String::operator!=(const char *other) const
{
	return not (operator==(other));
}

String String::peek(const char *string)
{
	return String(new Impl(string, 0u, false, false));
}

String String::copy(const char *string)
{
	return String(string[0] == 0
		? Impl::empty()
		: new Impl(copper_strndup(string, 0), 0u, false, true)
		);
}

String String::copy(const char *string, std::size_t size)
{
	return String(string[0] == 0
		? Impl::empty()
		: new Impl(copper_strndup(string, size), size, false, true)
		);
}

String String::steal(char *string)
{
	return String(new Impl(string, 0u, false, true));
}

String String::steal(char *string, std::size_t size)
{
	string[size] = 0;
	return String(new Impl(string, 0u, false, true));
}

String
String::build(const char *first, ...)
{
	// Work around namespace bug in TenDRA
	using namespace std;
	
	va_list args;
	size_t size;
	char *new_c_str, *part, *ii;
	
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
	
	return steal(new_c_str, size);
}

size_t String::size() const
{
	if (not p->have_size)
	{
		p->size = strlen(p->str);
		p->have_size = true;
	}
	
	return p->size;
}

const char *String::c_str() const
{
	return p->str;
}

}
