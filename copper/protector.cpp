/* protector.cpp -- Base class for all protectors
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#include <cassert>

#include "protector.hpp"
#include "test.hpp"
#include "util/list.hpp"

namespace Copper
{
	/** @class Protector
	 * Protectors guard against possible errors while running a test. This
	 * is an abstract interface for a Protector, which must be subclassed
	 * to be useful.
	 */

	List<Protector>&
	protectors () throw ()
	{
		static List<Protector> _protectors;
		return _protectors;
	}

	/** Default constructor */
	Protector::Protector () throw ()
	{
		add (this);
	}

	/** Default destructor */
	Protector::~Protector () throw ()
	{
	}

	/**
	 * Add a protector to the list of available protectors
	 * 
	 * @param protector The Protector to add
	 */
	void
	Protector::add (Protector *protector)
	{
		protectors ().append (protector);
	}

	/**
	 * Guard a test with all protectors currently available
	 * 
	 * @param test The test to guard
	 * 
	 * @return If an error occurred, a pointer to the error description.
	 *         If no error occurred, returns NULL.
	 */
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

	static
	bool
	test_matcher (const Protector *key, void *data)
	{
		return key == data;
	}

	/**
	 * Call the next protector in the global list to guard the test.
	 * 
	 * @param test The test to guard.
	 * 
	 * @return If an error occurred, a pointer to the error description.
	 *         If no error occurred, returns NULL.
	 */
	Error *
	Protector::next_protector (Test *test)
	{
		const ListNode<Protector>* node;
		node = protectors ().find (test_matcher, this);

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
