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
	Copper::String str;
	COPPER_ASSERT(equal(str.Size(), 0u));
	COPPER_ASSERT(StrcmpEqual(str.CStr(), ""));
}

COPPER_TEST(construct_no_size)
{
	Copper::String str("test");
	COPPER_ASSERT(equal(str.Size(), 4u));
	COPPER_ASSERT(StrcmpEqual(str.CStr(), "test"));
}

COPPER_TEST(construct_smaller_size)
{
	Copper::String str("test", 3);
	COPPER_ASSERT(equal(str.Size(), 3u));
	COPPER_ASSERT(StrcmpEqual(str.CStr(), "tes"));
}

COPPER_TEST(construct_larger_size)
{
	Copper::String str("test", 5);
	COPPER_ASSERT(equal(str.Size(), 4u));
	COPPER_ASSERT(StrcmpEqual(str.CStr(), "test"));
}

COPPER_TEST(copy_constructor)
{
	Copper::String first("test");
	Copper::String str(first);
	
	COPPER_ASSERT(equal(str.Size(), 4u));
	COPPER_ASSERT(StrcmpEqual(str.CStr(), "test"));
}

COPPER_TEST(copy_shared_string_data)
{
	Copper::String first("test");
	Copper::String str(first);
	
	// Check that the string wasn't actually copied
	COPPER_ASSERT(AddressEqual(str.CStr(), first.CStr()));
}

COPPER_TEST(from_static_ptr)
{
	const char *cstr = "test";
	Copper::String str = Copper::String::NoCopy(cstr);
	
	COPPER_ASSERT(AddressEqual(str.CStr(), cstr));
}

COPPER_TEST(from_static_array)
{
	const char cstr[] = "test";
	Copper::String str = Copper::String::FromStatic(cstr);
	
	COPPER_ASSERT(AddressEqual(str.CStr(), cstr));
}

COPPER_TEST(build_empty)
{
	Copper::String str = Copper::String::Build("", NULL);
	
	COPPER_ASSERT(equal(str.Size(), 0u));
	COPPER_ASSERT(StrcmpEqual(str.CStr(), ""));
}

COPPER_TEST(build)
{
	Copper::String str = Copper::String::Build("te", "st", NULL);
	
	COPPER_ASSERT(equal(str.Size(), 4u));
	COPPER_ASSERT(equal(str.CStr(), "test"));
	COPPER_ASSERT(StrcmpEqual(str.CStr(), "test"));
}

COPPER_TEST(assignment)
{
	Copper::String first("test");
	Copper::String str;
	str = first;
	
	COPPER_ASSERT(equal(str.Size(), 4u));
	COPPER_ASSERT(StrcmpEqual(str.CStr(), "test"));
}

COPPER_TEST(assign_shared_string_data)
{
	Copper::String first("test");
	Copper::String str;
	str = first;
	
	// Check that the string wasn't actually copied
	COPPER_ASSERT(AddressEqual(str.CStr(), first.CStr()));
}

COPPER_TEST(assign_to_self)
{
	Copper::String str("test");
	const char *before = str.CStr();
	str = str;
	
	COPPER_ASSERT(equal(str.Size(), 4u));
	COPPER_ASSERT(StrcmpEqual(str.CStr(), "test"));
	
	// Check that the string wasn't actually copied
	COPPER_ASSERT(AddressEqual(str.CStr(), before));
}

COPPER_TEST(equality)
{
	Copper::String a1("a"), a2("a"), b("b");
	COPPER_ASSERT(a1 == a2);
	COPPER_ASSERT(!(a1 == b));
}

COPPER_TEST(inequality)
{
	Copper::String a1("a"), a2("a"), b("b");
	COPPER_ASSERT(a1 != b);
	COPPER_ASSERT(!(a1 != a2));
}

}
