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

#ifndef COPPER_ASSERTIONS_HPP
#define COPPER_ASSERTIONS_HPP

#include <copper/AssertionResult.hpp>
#include <copper/repr.hpp>

template <class First, class Second>
Copper::AssertionResult equal
	( const First &first
	, const Second &second
	)
{
	using namespace Copper;
	
	if (first == second)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(first, "!=", second));
}

Copper::AssertionResult equal
	( const char *first
	, const char *second
	);

Copper::AssertionResult equal
	( const char *first
	, char second[]
	);

Copper::AssertionResult equal
	( char first[]
	, const char *second
	);

Copper::AssertionResult equal
	( char first[]
	, char second[]
	);

Copper::AssertionResult equal
	( const char *first
	, const Copper::String &second
	);

Copper::AssertionResult equal
	( char first[]
	, const Copper::String &second
	);

template <class Value>
Copper::AssertionResult equal_within
	( const Value &expected
	, const Value &actual
	, const Value &delta
	)
{
	using namespace Copper;
	
	if ((expected - delta < actual) && (expected + delta > actual))
	{ return AssertionResult::pass(); }
	
	String message = String::Build
		( repr(actual).CStr ()
		, " is not within "
		, repr(delta).CStr()
		, " of "
		, repr(expected).CStr()
		, NULL
		);
	return AssertionResult::fail(message);
}

template <class First, class Second>
Copper::AssertionResult unequal
	( const First &first
	, const Second &second
	)
{
	using namespace Copper;
	
	if (first != second)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(first, "==", second));
}

Copper::AssertionResult unequal
	( const char *first
	, const char *second
	);

Copper::AssertionResult unequal
	( const char *first
	, char second[]
	);

Copper::AssertionResult unequal
	( char first[]
	, const char *second
	);

Copper::AssertionResult unequal
	( char first[]
	, char second[]
	);

Copper::AssertionResult failed(const bool result);

Copper::AssertionResult failed(const Copper::AssertionResult &result);

template <class Value>
Copper::AssertionResult is_null(const Value *value)
{
	using namespace Copper;
	
	if (value == NULL)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, "!= NULL"));
}

template <class Value>
Copper::AssertionResult not_null(const Value *value)
{
	using namespace Copper;
	
	if (value != NULL)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, "== NULL"));
}

template <class Value>
Copper::AssertionResult greater_than
	( const Value &value
	, const Value &limit
	)
{
	using namespace Copper;
	
	if (value > limit)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, "<=", limit));
}

template <class Value>
Copper::AssertionResult greater_than_or_equal
	( const Value &value
	, const Value &limit
	)
{
	using namespace Copper;
	
	if (value >= limit)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, "<", limit));
}

template <class Value>
Copper::AssertionResult less_than
	( const Value &value
	, const Value &limit
	)
{
	using namespace Copper;
	
	if (value < limit)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, ">=", limit));
}

template <class Value>
Copper::AssertionResult less_than_or_equal
	( const Value &value
	, const Value &limit
	)
{
	using namespace Copper;
	
	if (value <= limit)
	{ return AssertionResult::pass(); }
	
	return AssertionResult::fail(repr_expr(value, ">", limit));
}

#endif
