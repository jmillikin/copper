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
#include <cstring>

using Copper::String;
using std::strcmp;

COPPER_SUITE(string_tests)
{

Copper::AssertionResult StrcmpEqual(const char *a, const char *b)
{
	return equal(0, strcmp(a, b));
}

Copper::AssertionResult AddressEqual(const char *a, const char *b)
{
	return equal((void*)a,(void*)b);
}

COPPER_TEST(construct_empty)
{
	String str;
	COPPER_ASSERT(equal(str.size(), 0u));
	COPPER_ASSERT(StrcmpEqual(str.c_str(), ""));
}

COPPER_TEST(construct_no_size)
{
	String str = String::copy("test");
	COPPER_ASSERT(equal(str.size(), 4u));
	COPPER_ASSERT(StrcmpEqual(str.c_str(), "test"));
}

COPPER_TEST(construct_smaller_size)
{
	String str = String::copy("test", 3);
	COPPER_ASSERT(equal(str.size(), 3u));
	COPPER_ASSERT(StrcmpEqual(str.c_str(), "tes"));
}

COPPER_TEST(construct_larger_size)
{
	String str = String::copy("test", 5);
	COPPER_ASSERT(equal(str.size(), 4u));
	COPPER_ASSERT(StrcmpEqual(str.c_str(), "test"));
}

COPPER_TEST(copy_constructor)
{
	String first = String::copy("test");
	String str(first);
	
	COPPER_ASSERT(equal(str.size(), 4u));
	COPPER_ASSERT(StrcmpEqual(str.c_str(), "test"));
}

COPPER_TEST(copy_shared_string_data)
{
	String first = String::copy("test");
	String str(first);
	
	// Check that the string wasn't actually copied
	COPPER_ASSERT(AddressEqual(str.c_str(), first.c_str()));
}

COPPER_TEST(from_static)
{
	const char *cstr = "test";
	String str = String::peek(cstr);
	
	COPPER_ASSERT(AddressEqual(str.c_str(), cstr));
}

COPPER_TEST(build_empty)
{
	String str = String::build("", NULL);
	
	COPPER_ASSERT(equal(str.size(), 0u));
	COPPER_ASSERT(StrcmpEqual(str.c_str(), ""));
}

COPPER_TEST(build)
{
	String str = String::build("te", "st", NULL);
	
	COPPER_ASSERT(equal(str.size(), 4u));
	COPPER_ASSERT(equal(str.c_str(), "test"));
	COPPER_ASSERT(StrcmpEqual(str.c_str(), "test"));
}

COPPER_TEST(assignment)
{
	String first = String::copy("test");
	String str;
	str = first;
	
	COPPER_ASSERT(equal(str.size(), 4u));
	COPPER_ASSERT(StrcmpEqual(str.c_str(), "test"));
}

COPPER_TEST(assign_shared_string_data)
{
	String first = String::copy("test");
	String str;
	str = first;
	
	// Check that the string wasn't actually copied
	COPPER_ASSERT(AddressEqual(str.c_str(), first.c_str()));
}

COPPER_TEST(assign_to_self)
{
	String str = String::copy("test");
	const char *before = str.c_str();
	str = str;
	
	COPPER_ASSERT(equal(str.size(), 4u));
	COPPER_ASSERT(StrcmpEqual(str.c_str(), "test"));
	
	// Check that the string wasn't actually copied
	COPPER_ASSERT(AddressEqual(str.c_str(), before));
}

COPPER_TEST(equality)
{
	String a1 = String::copy("a")
	     , a2 = String::copy("a")
	     , b = String::copy("b");
	COPPER_ASSERT(a1 == a2);
	COPPER_ASSERT(!(a1 == b));
}

COPPER_TEST(inequality)
{
	String a1 = String::copy("a")
	     , a2 = String::copy("a")
	     , b = String::copy("b");
	COPPER_ASSERT(a1 != b);
	COPPER_ASSERT(!(a1 != a2));
}

}
