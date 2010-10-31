/* ExceptionProtector.hpp -- Guards against unexpected exceptions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_EXCEPTION_PROTECTOR_HPP
#define COPPER_EXCEPTION_PROTECTOR_HPP

#include <copper/Protector.hpp>
#include <copper/FuncAttrs.hpp>

namespace Copper {

class COPPER_FUNCATTR_EXPORT ExceptionProtector : public Protector
{
public:
	ExceptionProtector ();
	~ExceptionProtector ();
	
protected:
	virtual Error *
	_guard (Test *test);
};

}

#endif
