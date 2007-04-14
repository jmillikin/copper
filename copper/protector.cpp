/* protector.cpp -- Base class for all protectors
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cassert>

#include <copper/protector.hpp>
#include <copper/test.hpp>
#include <copper/util/list.hpp>
#include "export.hpp"

namespace Copper
{
	List<Protector>&
	protectors () throw ()
	{
		static List<Protector> _protectors;
		return _protectors;
	}

	Protector::Protector () throw ()
	{
		add (this);
	}

	Protector::~Protector () throw ()
	{
	}

	EXPORT
	void
	Protector::add (Protector *protector)
	{
		protectors ().append (protector);
	}

	void
	Protector::guard (Test *test, Error **error)
	{
		if (protectors ().size () > 0)
			protectors ().root ()->value->_guard (test, error);

		else
			test->run ();
	}

	void
	Protector::next_protector (Test *test, Error **error)
	{
		const ListNode<Protector>* node = protectors ().find (this);

		assert (node);

		node = node->next;

		if (node)
			node->value->_guard (test, error);

		else
			// Reached the end of the list
			test->run ();
	}
}
