/* exception_protector.hpp -- Guards against unexpected exceptions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_EXCEPTION_PROTECTOR_HPP
#define COPPER_EXCEPTION_PROTECTOR_HPP

#include <copper/protector.hpp>
#include <copper/export.hpp>

namespace Copper
{
	class COPPER_EXPORT ExceptionProtector : public Protector {
	public:
		ExceptionProtector () throw ();

		~ExceptionProtector () throw ();

	protected:
		virtual
		Error *
		_guard (Test *test);
	} exception_protector_instance;
}

#endif /* COPPER_EXCEPTION_PROTECTOR_HPP */
