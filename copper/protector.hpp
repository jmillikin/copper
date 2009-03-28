/* protector.hpp -- Base class for all protectors
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_PROTECTOR_HPP
#define COPPER_PROTECTOR_HPP

#include <copper/compat.hpp>
#include <copper/error.hpp>
#include <copper/export.hpp>

namespace Copper
{
	class Test;
	class Assertion;

	class COPPER_EXPORT Protector
	{
	public:
		Protector ();

		virtual
		~Protector ();

		static
		void
		add (Protector *protector);

		static
		Error *
		guard (Test *test);

	protected:
		Error *
		next_protector (Test *test);

		/**
		 * Guard a test with this Protector. It is important that
		 * protectors be nested for them to work properly, so use
		 * next_protector () to do so.
		 * 
		 * @param test The test to guard.
		 * 
		 * @return If an error occurred, a pointer to the error
		 *         description. If no error occurred, returns NULL.
		 */
		virtual
		Error *
		_guard (Test *test) = 0;
	};
}

#endif /* COPPER_PROTECTOR_HPP */
