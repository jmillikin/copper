// Copyright (C) 2009-2010 John Millikin <jmillikin@gmail.com>
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

#ifndef COPPER_TEST_RUN_HPP
#define COPPER_TEST_RUN_HPP

#include <copper/String.hpp>

namespace Copper {

class AssertionResult;
class Error;
class Failure;
class Test;

class TestRun
{
public:
	// Called by test drivers
	//
	// Runs a test once, in a separate process. Sets 'out_failure' if
	// the test failed, 'out_error' if something unexpected went wrong,
	// or neither if the test passed.
	//
	// 'out_failure' and 'out_error', if set, must be deleted by the
	// caller.
	static void run_test
		( Test &test
		, Failure *&out_failure
		, Error *&out_error
		);
	
	// Called from tests
	//
	// Checks whether the assertion passed or failed, then writes a
	// message to the pipe and (if necessary) terminates the test
	// process.
	void assert
		( const AssertionResult &result
		, const char *text
		, const char *file
		, unsigned int line
		);
	
	void assert
		( bool result
		, const char *text
		, const char *file
		, unsigned int line
		);
	
	void fail
		( const char *message
		, const char *file
		, unsigned int line
		);
	
	void fail_throws
		( const char *exc_type
		, const char *code
		, const char *file
		, unsigned int line
		);
	
private:
	TestRun(int fd);
	
	void send_fail
		( const String &text
		, const String &message
		, const String &file
		, unsigned int line
		);
	
	void send_error(const String &message);
	
	int self_fd;
	bool self_error;
};

class Failure
{
public:
	Failure
		( const String &text
		, const String &message
		, const String &file
		, const unsigned int line
		);
	
	String Text;
	String Message;
	String File;
	unsigned int Line;
};

class Error
{
public:
	Error(const String &message);
	String Message;
};

}

#endif
