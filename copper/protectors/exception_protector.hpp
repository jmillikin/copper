/* exception_protector.hpp -- Guards against unexpected exceptions
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_EXCEPTION_PROTECTOR_HPP
#define COPPER_EXCEPTION_PROTECTOR_HPP

#include <copper/protector.hpp>

namespace Copper
{
	/** Guard against unknown exceptions being thrown by tests */
	class ExceptionProtector : public Protector {
	public:
		/** Default constructor */
		ExceptionProtector () throw ();

		/** Default destructor */
		~ExceptionProtector () throw ();

	protected:
		/**
		 * Guard a test with this Protector, to ensure it doesn't
		 * throw any weird exceptions.
		 * 
		 * @param test The Test to guard
		 * @param error If a protector caught an error, this will 
		 *              be changed to the error that was caught.
		*/
		virtual void _guard (Test *test, Error **error);
	} exception_protector_instance;
}

#endif /* COPPER_EXCEPTION_PROTECTOR_HPP */
