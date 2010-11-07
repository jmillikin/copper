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
#include <copper/List.hpp>
#include <copper/Test.hpp>
#include <copper/TestRun.hpp>

using std::strchr;

namespace Copper
{

struct MatchInfo
{
	const String &suite_name;
	const String &test_name;
};

static bool full_matcher(const Test *key, const void *data)
{
	const MatchInfo *info = static_cast <const MatchInfo *>(data);
	return (key->Name == info->test_name) &&
	       (key->Suite == info->suite_name);
}

static bool suite_matcher(const Test *key, const void *data)
{
	const MatchInfo *info = static_cast <const MatchInfo *>(data);
	return (key->Suite == info->suite_name);
}

static Test *find_test
	( const String &suite_name
	, const String &test_name
	)
{
	const ListNode<Test> *node;
	MatchInfo info = { suite_name, test_name };
	node = Test::all().find (full_matcher, &info);
	
	if (node)
	{ return node->value; }
	
	return NULL;
}


static List<Test> find_suite(const String &suite_name)
{
	MatchInfo info = { suite_name, "" };
	return Test::all().filter (suite_matcher, &info);
}

static List<Test> parse_test_args(int argc, char **argv)
{
	if (argc == 0)
	{
		return Test::all();
	}
	
	List<Test> tests;
	for (int ii = 0; ii < argc; ii++)
	{
		const char *name = argv[ii];
		const char *midpoint = strchr(name, '.');
		
		if (midpoint != NULL)
		{
			// This name includes a test name
			String suite_name(name, midpoint - name);
			String test_name(midpoint + 1);
			
			Test *test = find_test(suite_name, test_name);
			if (test != NULL)
			{
				tests.append(test);
			}
		}
		
		else
		{
			// No test name, append everything in the suite
			tests.extend(find_suite(name));
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
	
	List<Test> tests = parse_test_args(argc - 1, argv + 1);
	
	const ListNode<Test> *node = NULL;
	while (tests.each(&node))
	{
		Test &test = *(node->value);
		Failure *failure;
		Error *error;
		
		TestRun::run_test(test, failure, error);
		
		if (failure != NULL)
		{
			count_fail++;
			fprintf( stderr
			       , "FAILURE in %s:%u:\n"
			         "%s.%s:\n"
			         "\t%s\n"
			         "\t%s\n\n"
			       , test.FileName.CStr(), failure->Line
			       , test.Suite.CStr(), test.Name.CStr()
			       , failure->Text.CStr()
			       , failure->Message.CStr()
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
			       , test.FileName.CStr()
			       , test.Suite.CStr(), test.Name.CStr()
			       , error->Message.CStr()
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
