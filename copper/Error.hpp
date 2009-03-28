/* error.hpp -- Created when an execution error occurs
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_ERROR_HPP
#define COPPER_ERROR_HPP

#include <copper/String.hpp>

namespace Copper
{
	class Error
	{
	public:
		Error (const String &message);

		~Error ();

		const String message;

	private:
		Error &
		operator= (const Error&);
	};
}

#endif /* COPPER_ERROR_HPP */
