/* list.hpp -- A generic append-only list
 * Copyright (C) 2006-2007 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifndef COPPER_UTIL_LIST_HPP
#define COPPER_UTIL_LIST_HPP

#include <cstddef>

namespace Copper
{
	/**
	 * @brief A single node in a List
	 * 
	 * Stores information on a single list node, including the next node
	 * in the list and the stored pointer.
	 */
	template <class C>
	struct ListNode
	{
		/**
		 * @brief Constructs a new ListNode.
		 * 
		 * The resulting node should be added to the end of the list.
		 * 
		 * @param value The value the node will contain.
		 */
		ListNode (C *value):
		          next (NULL),
		          value (value)
		{
		}

		/**
		 * @brief The next node in the list, or NULL.
		 */
		ListNode *next;

		/**
		 * @brief The value stored in this node.
		 */
		C *value;
	};

	/**
	 * @brief A generic append-only list
	 * 
	 * Implements a generic linked list. Only appending to the list is
	 * allowed - elements may not be moved or deleted. Only pointers may
	 * be stored.
	 */
	template <class C>
	class List
	{
	public:
		/**
		 * @brief A function to check if key is the key being searched
		 *        for, with user data.
		 * 
		 * @param key The key to check.
		 * @param data User-defined data, to be used for checking the
		 *             key.
		 * 
		 * @return whether key is the key being searched for.
		 */
		typedef bool (type_matcher)(const C *key, const void *data);

		/**
		 * @brief Constructs a new, empty list.
		 */
		List ():
		      _root (NULL),
		      _size (0)
		{
		}

		/**
		 * @brief Constructs a list as a copy of another list.
		 * 
		 * Data items are not copied, so be careful about deleting
		 * them if there is a copied list hanging around.
		 * 
		 * @param other The list to copy.
		 */
		List (const List &other):
		      _root (NULL),
		      _size (0)
		{
			extend (other);
		}

		/**
		 * @brief Sets this list to be a copy of another list.
		 * 
		 * Data items are not copied, so be careful about deleting
		 * them if there is a copied list hanging around.
		 * 
		 * @param other The list to copy.
		 * 
		 * @return a reference to this list.
		 */
		List &
		operator= (const List &other)
		{
			clear ();
			extend (other);
			return *this;
		}

		/**
		 * @brief Deallocate memory used by the list.
		 * 
		 * Note that this does not deallocate data items - that
		 * must be done manually.
		 */
		~List ()
		{
			clear ();
		}

		/**
		 * @brief Appends a new item to the list.
		 * 
		 * Ownership of the item is not transferred, so be sure not
		 * to deallocate it until after the list is no longer needed.
		 * 
		 * @param value The item to append
		 */
		void
		append (C *value)
		{
			if (_root)
			{
				ListNode<C> *last = _root;
				while (last->next)
				{
					last = last->next;
				}

				last->next = new ListNode<C> (value);
			}

			else
			{
				_root = new ListNode<C> (value);
			}

			++_size;
		}

		/**
		 * @brief Search for a value in the list
		 * 
		 * Searches the list for a value that matches a particular
		 * function. The first node for which the function returns
		 * true will be returned.
		 * 
		 * @param matches A function which should return true if the
		 *                given data is what is being searched for.
		 * @param data User-defined data to pass to matches.
		 * 
		 * @return the list node containing the given key, or NULL
		 *         if the key was not found.
		 */
		const ListNode<C> *
		find (type_matcher *matches, const void *data) const
		{
			const ListNode<C> *node = NULL;
			while (each (&node))
				if (matches (node->value, data))
					return node;
			
			return NULL;
		}

		/**
		 * @brief Filter the list through a function
		 * 
		 * Searches the list for all values that match a particular
		 * function, and return a list of such values.
		 * 
		 * @param matches A function which should return true if the
		 *                given data is what is being searched for.
		 * @param data User-defined data to pass to matches.
		 * 
		 * @return a list of values matching the given function.
		 */
		List<C>
		filter (type_matcher *matches, const void *data) const
		{
			List<C> new_list;
			const ListNode<C> *node = NULL;
			while (each (&node))
				if (matches (node->value, data))
					new_list.append (node->value);
			
			return new_list;
		}

		/**
		 * @brief Returns the first node in the list.
		 * 
		 * @return the first node in the list, or NULL if the list is
		 *         empty.
		 */
		const ListNode<C> *
		root () const
		{
			return _root;
		}

		/**
		 * @brief Returns the size of the list.
		 * 
		 * @return the size of the list.
		 */
		std::size_t
		size () const
		{
			return _size;
		}

		/**
		 * @brief Appends all items of another list to this list.
		 * 
		 * @param other The list to copy from.
		 */
		void
		extend (const List<C> &other)
		{
			const ListNode<C> *node = NULL;
			while (other.each (&node))
				append (node->value);
		}
		
		/**
		 * @brief Iterate through the list
		 * 
		 * ListNode<C> value;
		 * while (list.each (&value))
		 * {
		 *   ...
		 * }
		 * 
		 * @param
		**/
		bool
		each (const ListNode<C> **node_ptr) const
		{
			const ListNode<C> *node = *node_ptr;
			
			if (node)
			{
				if (node->next)
				{
					*node_ptr = node->next;
					return true;
				}
				
				else
				{
					*node_ptr = NULL;
					return false;
				}
			}
			
			else
			{
				*node_ptr = root ();
				return (*node_ptr != NULL);
			}
		}
		
	private:
		void clear ()
		{
			ListNode<C> *node = _root, *next;
			while (node)
			{
				next = node->next;
				delete node;
				node = next;
			}
			_root = NULL;
			_size = 0;
		}

		ListNode<C> *_root;
		std::size_t _size;
	};
}

#endif /* COPPER_UTIL_LIST_HPP */
