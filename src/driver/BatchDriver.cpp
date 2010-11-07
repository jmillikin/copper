// Copyright (C) 2010 John Millikin <jmillikin@gmail.com>
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

#include <cstdio>
#include <cstring>

#include <copper/driver/BatchDriver.hpp>
#include <copper/Test.hpp>
#include <copper/TestRun.hpp>

using std::strchr;

namespace Copper
{

static Test *find_test
	( const String &suite_name
	, const String &test_name
	)
{
	TestList::iterator iter;
	
	Test *test;
	while (Test::all().each(iter, &test))
	{
		if (test->name == test_name &&
		    test->suite == suite_name)
		{
			return test;
		}
	}
	
	return NULL;
}

static TestList find_suite(const String &suite_name)
{
	TestList tests;
	TestList::iterator iter;
	
	Test *test;
	while (Test::all().each(iter, &test))
	{
		if (test->suite == suite_name)
		{
			tests.append(*test);
		}
	}
	
	return tests;
}

static TestList parse_test_args(int argc, char **argv)
{
	if (argc == 0)
	{
		return Test::all();
	}
	
	TestList tests;
	for (int ii = 0; ii < argc; ii++)
	{
		const char *name = argv[ii];
		const char *midpoint = strchr(name, '.');
		
		if (midpoint != NULL)
		{
			// This name includes a test name
			String suite_name = String::copy(name, midpoint - name);
			String test_name = String::copy(midpoint + 1);
			
			Test *test = find_test(suite_name, test_name);
			if (test != NULL)
			{
				tests.append(*test);
			}
		}
		
		else
		{
			// No test name, append everything in the suite
			tests.extend(find_suite(String::peek(name)));
		}
	}
	
	return tests;
}

int BatchDriver::run (int argc, char **argv)
{
	// Work around namespace bug in TenDRA
	using namespace std;
	
	unsigned int count_pass = 0
	           , count_fail = 0
	           , count_error = 0;
	
	TestList tests = parse_test_args(argc - 1, argv + 1);
	TestList::iterator iter;
	
	Test *test;
	while (tests.each(iter, &test))
	{
		Failure *failure;
		Error *error;
		
		TestRun::run_test(*test, failure, error);
		
		if (failure != NULL)
		{
			count_fail++;
			fprintf( stderr
			       , "FAILURE in %s:%u:\n"
			         "%s.%s:\n"
			         "\t%s\n"
			         "\t%s\n\n"
			       , test->file_name.c_str(), failure->line
			       , test->suite.c_str(), test->name.c_str()
			       , failure->text.c_str()
			       , failure->message.c_str()
			       );
			delete failure;
		}
		
		else if (error != NULL)
		{
			count_error++;
			fprintf( stderr
			       , "ERROR in %s:\n"
			         "%s.%s:\n"
			         "\t%s\n\n"
			       , test->file_name.c_str()
			       , test->suite.c_str(), test->name.c_str()
			       , error->message.c_str()
			       );
			delete error;
		}
		
		else
		{
			count_pass++;
		}
	}
	
	// Print statistics
	printf( "%u tests passed\n"
	        "%u tests failed\n"
	        "%u errors\n"
	      , count_pass
	      , count_fail
	      , count_error
	      );
	
	if ((count_fail + count_error) > 0)
	{ return 1; }
	
	return 0;
}

}
