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

#include <copper.hpp>

using Copper::repr;

// Can't use normal limits, since they change from system to system
const signed short MY_SHRT_MIN = -32768;
const signed short MY_SHRT_MAX = 32767;

const unsigned short MY_USHRT_MAX = 65535;

const signed int MY_INT_MAX = 2147483647;
const signed int MY_INT_MIN = -MY_INT_MAX - 1;

const unsigned int MY_UINT_MAX = 4294967295U;

const signed long MY_LONG_MAX = 2147483647L;
const signed long MY_LONG_MIN = -MY_LONG_MAX - 1;

const unsigned long MY_ULONG_MAX = 4294967295UL;

COPPER_SUITE(repr)
{

COPPER_TEST(bool)
{
	COPPER_ASSERT(equal("true", repr(true)));
	COPPER_ASSERT(equal("false", repr(false)));
}

COPPER_TEST(char)
{
	// Non-printable characters
	COPPER_ASSERT(equal("'\\x01'", repr((char)0x01)));
	COPPER_ASSERT(equal("'\\x0F'", repr((char)0x0F)));
	COPPER_ASSERT(equal("'\\x1F'", repr((char)0x1F)));
	COPPER_ASSERT(equal("'\\x7F'", repr((char)0x7F)));
	COPPER_ASSERT(equal("'\\xFF'", repr((char)0xFF)));
	
	// Special cases
	COPPER_ASSERT(equal("'\\''", repr('\'')));
	COPPER_ASSERT(equal("'\\\\'", repr('\\')));
	
	// Standard printable
	COPPER_ASSERT(equal("' '", repr(' ')));
	COPPER_ASSERT(equal("'A'", repr('A')));
	COPPER_ASSERT(equal("'~'", repr('~')));
}

COPPER_TEST(string)
{
	// Non-printable characters
	COPPER_ASSERT(equal("\"\\x01\"", repr("\x01")));
	COPPER_ASSERT(equal("\"\\x0F\"", repr("\x0F")));
	COPPER_ASSERT(equal("\"\\x1F\"", repr("\x1F")));
	COPPER_ASSERT(equal("\"\\x7F\"", repr("\x7F")));
	COPPER_ASSERT(equal("\"\\xFF\"", repr("\xFF")));
	
	// Special cases
	COPPER_ASSERT(equal("\"\\\"\"", repr("\"")));
	COPPER_ASSERT(equal("\"\\\\\"", repr("\\")));
	
	// Standard printable
	COPPER_ASSERT(equal("\" \"", repr(" ")));
	COPPER_ASSERT(equal("\"A\"", repr("A")));
	COPPER_ASSERT(equal("\"~\"", repr("~")));
}

COPPER_TEST(signed_short)
{
	signed short neg_one = -1, pos_one = 1, zero = 0;
	COPPER_ASSERT(equal("-1", repr(neg_one)));
	COPPER_ASSERT(equal("1", repr(pos_one)));
	COPPER_ASSERT(equal("0", repr(zero)));
	
	// Check limits
	COPPER_ASSERT(equal("-32768", repr(MY_SHRT_MIN)));
	COPPER_ASSERT(equal("32767", repr(MY_SHRT_MAX)));
}

COPPER_TEST(unsigned_short)
{
	unsigned short pos_one = 1, zero = 0;
	COPPER_ASSERT(equal("1", repr(pos_one)));
	COPPER_ASSERT(equal("0", repr(zero)));
	
	// Check limits */
	COPPER_ASSERT(equal("65535", repr(MY_USHRT_MAX)));
}

COPPER_TEST(signed_int)
{
	signed int neg_one = -1, pos_one = 1, zero = 0;
	COPPER_ASSERT(equal("-1", repr(neg_one)));
	COPPER_ASSERT(equal("1", repr(pos_one)));
	COPPER_ASSERT(equal("0", repr(zero)));
	
	// Check limits
	COPPER_ASSERT(equal("-2147483648", repr(MY_INT_MIN)));
	COPPER_ASSERT(equal("2147483647", repr(MY_INT_MAX)));
}

COPPER_TEST(unsigned_int)
{
	unsigned int pos_one = 1, zero = 0;
	COPPER_ASSERT(equal("1", repr(pos_one)));
	COPPER_ASSERT(equal("0", repr(zero)));
	
	// Check limits
	COPPER_ASSERT(equal("4294967295", repr(MY_UINT_MAX)));
}

COPPER_TEST(signed_long)
{
	signed long neg_one = -1, pos_one = 1, zero = 0;
	COPPER_ASSERT(equal("-1", repr(neg_one)));
	COPPER_ASSERT(equal("1", repr(pos_one)));
	COPPER_ASSERT(equal("0", repr(zero)));
	
	// Check limits
	COPPER_ASSERT(equal("-2147483648", repr(MY_LONG_MIN)));
	COPPER_ASSERT(equal("2147483647", repr(MY_LONG_MAX)));
}

COPPER_TEST(unsigned_long)
{
	unsigned long pos_one = 1, zero = 0;
	COPPER_ASSERT(equal("1", repr(pos_one)));
	COPPER_ASSERT(equal("0", repr(zero)));
	
	// Check limits
	COPPER_ASSERT(equal("4294967295", repr(MY_ULONG_MAX)));
}

COPPER_TEST(float)
{
	COPPER_ASSERT(equal("1.2345", repr(1.2345f)));
}

COPPER_TEST(double)
{
	COPPER_ASSERT(equal("1.2345", repr(1.2345)));
}

COPPER_TEST(Copper_String)
{
	COPPER_ASSERT(equal
		( "\"some_string\""
		, repr(Copper::String("some_string"))
		));
}

}
