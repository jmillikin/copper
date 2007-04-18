/* error.hpp -- Created when an execution error occurs
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_ERROR_HPP
#define COPPER_ERROR_HPP

#include <copper/util/string.hpp>

namespace Copper
{
	class Error
	{
	public:
		Error (const String &message) throw ();

		~Error () throw ();

		const String message;

	private:
		Error &
		operator= (const Error&) throw ();

		Error (const Error&) throw ();
	};
}

#endif /* COPPER_ERROR_HPP */
