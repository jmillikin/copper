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

#include <cstring>
#include <cstdlib>

#include <copper/AssertionResult.hpp>

namespace Copper
{

AssertionResult::AssertionResult(bool passed, const String &message)
	: passed(passed)
	, message(message)
{
}

AssertionResult::operator bool() const
{
	return passed;
}

AssertionResult AssertionResult::pass()
{
	return AssertionResult(true, "");
}

AssertionResult AssertionResult::fail(const String &message)
{
	return AssertionResult(false, message);
}

}
