// Copyright (C) 2007-2010 John Millikin <jmillikin@gmail.com>
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

COPPER_SUITE(list)
{

COPPER_TEST(constructor)
{
	Copper::List<int> a;
	
	COPPER_ASSERT(is_null(a.root()));
	COPPER_ASSERT(equal(0u, a.size()));
}

COPPER_TEST(copy_constructor)
{
	int i;
	Copper::List<int> a;
	a.append(&i);
	
	Copper::List<int> b(a);
	
	COPPER_ASSERT(not_null(b.root()));
	COPPER_ASSERT(equal(b.root()->value, &i));
	COPPER_ASSERT(equal(1u, b.size()));
}

COPPER_TEST(copy_constructor_empty)
{
	Copper::List<int> a, b(a);
	
	COPPER_ASSERT(is_null(b.root()));
	COPPER_ASSERT(equal(0u, b.size()));
}

COPPER_TEST(assignment)
{
	int i, j;
	Copper::List<int> a, b;
	a.append(&i);
	b.append(&j);
	
	a = b;
	
	COPPER_ASSERT(not_null(a.root()));
	COPPER_ASSERT(equal(a.root()->value, &j));
	COPPER_ASSERT(equal(1u, a.size()));
}

COPPER_TEST(assignment_empty)
{
	int i;
	Copper::List<int> a, b;
	a.append(&i);
	
	a = b;
	
	COPPER_ASSERT(is_null(a.root()));
	COPPER_ASSERT(equal(0u, a.size()));
}

COPPER_TEST(append)
{
	int i;
	Copper::List<int> a;
	a.append(&i);
	
	COPPER_ASSERT(not_null(a.root()));
	COPPER_ASSERT(equal(a.root()->value, &i));
	COPPER_ASSERT(equal(1u, a.size()));
}

COPPER_TEST(extend)
{
	int i, j;
	Copper::List<int> a, b;
	a.append(&i);
	b.append(&j);
	
	a.extend(b);
	COPPER_ASSERT(not_null(a.root()));
	COPPER_ASSERT(equal(2u, a.size()));
	COPPER_ASSERT(equal(a.root()->value, &i));
	COPPER_ASSERT(equal(a.root()->next->value, &j));
}

}
