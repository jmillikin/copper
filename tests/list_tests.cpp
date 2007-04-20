/* list_tests.cpp -- Testing the Copper::List utility class
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <copper.hpp>

TEST_SUITE (list_tests)
{
	TEST (constructor)
	{
		Copper::List<int> a;

		ASSERT (is_null (a.root ()));
		ASSERT (equal (0u, a.size ()));
	}

	TEST (copy_constructor)
	{
		int i;
		Copper::List<int> a;
		a.append (&i);

		Copper::List<int> b (a);

		ASSERT (not_null (b.root ()));
		ASSERT (equal (b.root ()->value, &i));
		ASSERT (equal (1u, b.size ()));
	}

	TEST (copy_constructor_empty)
	{
		Copper::List<int> a, b (a);

		ASSERT (is_null (b.root ()));
		ASSERT (equal (0u, b.size ()));
	}

	TEST (assignment)
	{
		int i, j;
		Copper::List<int> a, b;
		a.append (&i);
		b.append (&j);

		a = b;

		ASSERT (not_null (a.root ()));
		ASSERT (equal (a.root ()->value, &j));
		ASSERT (equal (1u, a.size ()));
	}

	TEST (assignment_empty)
	{
		int i;
		Copper::List<int> a, b;
		a.append (&i);

		a = b;

		ASSERT (is_null (a.root ()));
		ASSERT (equal (0u, a.size ()));
	}

	TEST (append)
	{
		int i;
		Copper::List<int> a;
		a.append (&i);

		ASSERT (not_null (a.root ()));
		ASSERT (equal (a.root ()->value, &i));
		ASSERT (equal (1u, a.size ()));
	}

	TEST (extend)
	{
		int i, j;
		Copper::List<int> a, b;
		a.append (&i);
		b.append (&j);

		a.extend (b);
		ASSERT (not_null (a.root ()));
		ASSERT (equal (2u, a.size ()));
		ASSERT (equal (a.root ()->value, &i));
		ASSERT (equal (a.root ()->next->value, &j));
	}
}
