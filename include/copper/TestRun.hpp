/* TestRun.hpp -- Information on one run of a test
 * Copyright (C) 2009 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_TEST_RUN_HPP
#define COPPER_TEST_RUN_HPP

#include <copper/FuncAttrs.hpp>

namespace Copper {

class Test;
class AssertionResult;

class COPPER_FUNCATTR_EXPORT TestRun
{
public:
	TestRun (Test *test);
	virtual ~TestRun ();
	
	virtual bool
	Assert (const AssertionResult &result,
	        const char *text,
	        const char *file,
	        unsigned int line) = 0;
	
	virtual bool
	Assert (bool result,
	        const char *text,
	        const char *file,
	        unsigned int line);
	
	virtual bool
	Fail (const char *message,
	      const char *file,
	      unsigned int line) = 0;
	
	virtual bool
	AssertThrowsFailed (const char *exc_type,
	                    const char *code,
	                    const char *file,
	                    unsigned int line) = 0;
	
	virtual void
	Run ();
	
protected:
	Test *test;
};

}

#endif
