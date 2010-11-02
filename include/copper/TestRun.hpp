/* TestRun.hpp -- Information on one run of a test
 * Copyright (C) 2009 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_RUN_HPP
#define COPPER_TEST_RUN_HPP

namespace Copper {

class AssertionResult;
class Error;
class Failure;
class String;
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
	TestRun (int fd);
	
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

}

#endif
