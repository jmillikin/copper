/* failure.cpp -- Records the failure of a test
 * Copyright (C) 2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include "export.hpp"
#include "failure.hpp"

namespace Copper
{
	EXPORT
	Failure::Failure (const char *_text,
	                  const char *_message,
	                  const char *_file,
	                  const unsigned int _line) throw ():

	                  text (_text),
	                  message (_message),
	                  file (_file),
	                  line (_line)
	{
	}
	EXPORT
	Failure::Failure (const String &_text,
	                  const String &_message,
	                  const String &_file,
	                  const unsigned int _line) throw ():

	                  text (_text),
	                  message (_message),
	                  file (_file),
	                  line (_line)
	{
	}

	EXPORT
	Failure::~Failure () throw ()
	{
	}
}
