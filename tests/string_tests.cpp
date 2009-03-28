/* string_tests.cpp -- Tests of equal () and unequal () on strings
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>
#include <cstring>

using std::strcmp;

SUITE (string_tests)
{
	Copper::AssertionResult StrcmpEqual (const char *a, const char *b)
	{
		return equal (0, strcmp (a, b));
	}
	
	Copper::AssertionResult AddressEqual (const char *a, const char *b)
	{
		return equal ((int)a, (int)b);
	}
	
	TEST (construct_empty)
	{
		Copper::String str;
		ASSERT (equal (str.Size (), 0u));
		ASSERT (StrcmpEqual (str.CStr (), ""));
	}
	
	TEST (construct_no_size)
	{
		Copper::String str ("test");
		ASSERT (equal (str.Size (), 4u));
		ASSERT (StrcmpEqual (str.CStr (), "test"));
	}
	
	TEST (construct_smaller_size)
	{
		Copper::String str ("test", 3);
		ASSERT (equal (str.Size (), 3u));
		ASSERT (StrcmpEqual (str.CStr (), "tes"));
	}
	
	TEST (construct_larger_size)
	{
		Copper::String str ("test", 5);
		ASSERT (equal (str.Size (), 4u));
		ASSERT (StrcmpEqual (str.CStr (), "test"));
	}
	
	TEST (copy_constructor)
	{
		Copper::String first ("test");
		Copper::String str (first);
		
		ASSERT (equal (str.Size (), 4u));
		ASSERT (StrcmpEqual (str.CStr (), "test"));
	}
	
	TEST (copy_shared_string_data)
	{
		Copper::String first ("test");
		Copper::String str (first);
		
		// Check that the string wasn't actually copied
		ASSERT (AddressEqual (str.CStr (), first.CStr ()));
	}
	
	TEST (from_static_ptr)
	{
		const char *cstr = "test";
		Copper::String str = Copper::String::NoCopy (cstr);
		
		ASSERT (AddressEqual (str.CStr (), cstr));
	}
	
	TEST (from_static_array)
	{
		const char cstr[] = "test";
		Copper::String str = Copper::String::FromStatic (cstr);
		
		ASSERT (AddressEqual (str.CStr (), cstr));
	}
	
	TEST (build_empty)
	{
		Copper::String str = Copper::String::Build ("", NULL);
		
		ASSERT (equal (str.Size (), 0u));
		ASSERT (StrcmpEqual (str.CStr (), ""));
	}
	
	TEST (build)
	{
		Copper::String str = Copper::String::Build ("te", "st", NULL);
		
		ASSERT (equal (str.Size (), 4u));
		ASSERT (equal (str.CStr (), "test"));
		ASSERT (StrcmpEqual (str.CStr (), "test"));
	}
	
	TEST (assignment)
	{
		Copper::String first ("test");
		Copper::String str;
		str = first;
		
		ASSERT (equal (str.Size (), 4u));
		ASSERT (StrcmpEqual (str.CStr (), "test"));
	}
	
	TEST (assign_shared_string_data)
	{
		Copper::String first ("test");
		Copper::String str;
		str = first;
		
		// Check that the string wasn't actually copied
		ASSERT (AddressEqual (str.CStr (), first.CStr ()));
	}
	
	TEST (assign_to_self)
	{
		Copper::String str ("test");
		const char *before = str.CStr ();
		str = str;
		
		ASSERT (equal (str.Size (), 4u));
		ASSERT (StrcmpEqual (str.CStr (), "test"));
		
		// Check that the string wasn't actually copied
		ASSERT (AddressEqual (str.CStr (), before));
	}
	
	TEST (equality)
	{
		Copper::String a1 ("a"), a2 ("a"), b ("b");
		ASSERT (a1 == a2);
		ASSERT (!(a1 == b));
	}
	
	TEST (inequality)
	{
		Copper::String a1 ("a"), a2 ("a"), b ("b");
		ASSERT (a1 != b);
		ASSERT (!(a1 != a2));
	}
}
