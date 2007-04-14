/* error.hpp - Created when an execution error occurs
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_ERROR_HPP
#define COPPER_ERROR_HPP

#include <copper/util/string.hpp>

namespace Copper
{
	/**
	 * This is used to indicate that something unexpected went wrong running a test
	 */
	class Error
	{
	public:
		/**
		 * Default constructor
		 * 
		 * @param message The error string
		 */
		Error (const String &message) throw ();

		/** Default constructor */
		~Error () throw ();

		/** The error that occurred */
		const String message;

	private:
		Error &
		operator= (const Error&) throw ();

		Error (const Error&) throw ();
	};
}

#endif /* COPPER_ERROR_HPP */
