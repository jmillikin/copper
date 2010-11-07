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

#include <cstdio>

#include <copper/repr.hpp>

static const char *HEX = "0123456789ABCDEF";

// Should be large enough for any integral type (int, long, etc)
//
// Also large enough for floating-point values, assuming %g format
static const std::size_t SPRINTF_BUF_SIZE = 40;

namespace Copper {

#if HAVE_BOOLEAN
String repr(const bool v)
{
	return String::FromStatic (v ? "true" : "false");
}
#endif

String repr(const char v)
{
	char buffer[7] = {'\'', '\\', '\'', '\'', '\'', '\'', '\0'};
	if (v < ' ' || v > '~')
	{
		buffer[2] = 'x';
		buffer[3] = HEX[(v & 0xF0) >> 4];
		buffer[4] = HEX[v & 0xF];
	}
	else if (v == '\\' || v == '\'')
	{
		buffer[2] = v;
		buffer[4] = '\0';
	}
	
	else
	{
		buffer[1] = v;
		buffer[3] = '\0';
	}
	return String(buffer);
}

String repr(const char *v)
{
	using std::size_t;
	
	if (v == NULL)
	{ return String::NoCopy("NULL"); }
	
	size_t len = 0;
	bool clean = true;
	char c;
	while ((c = v[len]) != 0)
	{
		if (c < ' ' || c > '~' || c == '"' || c == '\\')
		{ clean = false; }
		
		++len;
	}
	
	if (clean)
	{ return String::Build("\"", v, "\"", NULL); }
	
	// Each char can expand to \xAA; two chars for quotes
	char *buf = new char[(len * 4) + 2];
	
	size_t buf_len = 0;
	buf[buf_len++] = '\"';
	for (size_t ii = 0; ii < len; ++ii)
	{
		c = v[ii];
		if (c < ' ' || c > '~')
		{
			buf[buf_len++] = '\\';
			buf[buf_len++] = 'x';
			buf[buf_len++] = HEX[(c & 0xF0) >> 4];
			buf[buf_len++] = HEX[c & 0xF];
		}
		else if (c == '\\' || c == '"')
		{
			buf[buf_len++] = '\\';
			buf[buf_len++] = c;
		}
		
		else
		{
			buf[buf_len++] = c;
		}
	}
	buf[buf_len++] = '\"';
	
	String result = String(buf, buf_len);
	delete[] buf;
	return result;
}

String repr(const String &v)
{
	return repr(v.CStr());
}

String repr(const signed char v)
{
	return repr(static_cast<char>(v));
}

String repr(const unsigned char v)
{
	return repr(static_cast<char>(v));
}

String repr(const signed short v)
{
	char buffer[SPRINTF_BUF_SIZE];
	std::sprintf(buffer, "%hd", v);
	return String(buffer);
}

String repr(const signed int v)
{
	char buffer[SPRINTF_BUF_SIZE];
	std::sprintf(buffer, "%d", v);
	return String(buffer);
}

String repr(const signed long v)
{
	char buffer[SPRINTF_BUF_SIZE];
	std::sprintf(buffer, "%ld", v);
	return String(buffer);
}

String repr(const unsigned short v)
{
	char buffer[SPRINTF_BUF_SIZE];
	std::sprintf(buffer, "%hu", v);
	return String(buffer);
}

String repr(const unsigned int v)
{
	char buffer[SPRINTF_BUF_SIZE];
	std::sprintf(buffer, "%u", v);
	return String(buffer);
}

String repr(const unsigned long v)
{
	char buffer[SPRINTF_BUF_SIZE];
	std::sprintf(buffer, "%lu", v);
	return String(buffer);
}

String repr(const float v)
{
	char buffer[SPRINTF_BUF_SIZE];
	std::sprintf(buffer, "%g", v);
	return String(buffer);
}

String repr(const double v)
{
	char buffer[SPRINTF_BUF_SIZE];
	std::sprintf(buffer, "%g", v);
	return String(buffer);
}

}
