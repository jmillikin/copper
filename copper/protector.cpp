/* protector.cpp -- Base class for all protectors
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cassert>

#include "export.hpp"
#include "protector.hpp"
#include "test.hpp"
#include "util/list.hpp"

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

	Error *
	Protector::guard (Test *test)
	{
		if (protectors ().size () > 0)
		{
			Protector *p = protectors ().root ()->value;
			return p->_guard (test);
		}

		else
		{
			test->run ();
			return NULL;
		}
	}

	Error *
	Protector::next_protector (Test *test)
	{
		const ListNode<Protector>* node = protectors ().find (this);

		assert (node);

		node = node->next;

		if (node)
		{
			return node->value->_guard (test);
		}

		else
		{
			// Reached the end of the list
			test->run ();
			return NULL;
		}
	}
}
