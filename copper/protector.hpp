/* protector.hpp -- Base class for all protectors
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_PROTECTOR_HPP
#define COPPER_PROTECTOR_HPP

#include <copper/compat.hpp>
#include <copper/error.hpp>

namespace Copper
{
	class Test;
	class Assertion;

	/**
	 * Protectors guard against possible errors while running a test. This
	 * is an abstract interface for a Protector, which must be subclassed
	 * to be useful.
	 */
	class Protector
	{
	public:
		/** Default constructor */
		Protector () throw ();

		/** Default destructor */
		virtual
		~Protector () throw ();

		/**
		 * Add a protector to the list of available protectors
		 * 
		 * @param protector The Protector to add
		 */
		static
		void
		add (Protector *protector);

		/**
		 * Guard a test with all protectors currently available
		 * 
		 * @param test The Test to guard
		 * 
		 * @return If an error occurred, a pointer to the error
		 * description. If no error occurred, returns NULL.
		 */
		static
		Error *
		guard (Test *test);

	protected:
		/**
		 * Call the next Protector in the global list to guard the test
		 * 
		 * @param test The Test to guard
		 * 
		 * @return If an error occurred, a pointer to the error
		 * description. If no error occurred, returns NULL.
		 */
		Error *
		next_protector (Test *test);

		/**
		 * Guard a test with this Protector. It is important that
		 * protectors be nested for them to work properly, so use
		 * next_protector () to do so.
		 * 
		 * @param test The Test to guard
		 * 
		 * @return If an error occurred, a pointer to the error
		 * description. If no error occurred, returns NULL.
		 */
		virtual
		Error *
		_guard (Test *test) = 0;
	};
}

#endif /* COPPER_PROTECTOR_HPP */
