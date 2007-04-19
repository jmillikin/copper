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
		 * @brief Constructs a new, empty list.
		 */
		List () throw ():
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
			if (!other._root)
				return;

			_root = new ListNode<C> (other._root->value);

			ListNode<C> *node = _root, *b_node = other._root->next;

			while (b_node)
			{
				node->next = new ListNode<C> (b_node->value);
				node = node->next;
				b_node = b_node->next;
			}

			_size = other._size;
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
			if (!other._root)
			{
				_root = NULL;
				_size = 0;
				return *this;
			}

			_root = new ListNode<C> (other._root->value);

			ListNode<C> *node = _root, *b_node = other._root->next;

			while (b_node)
			{
				node->next = new ListNode<C> (b_node->value);
				node = node->next;
				b_node = b_node->next;
			}

			_size = other._size;
			return *this;
		}

		/**
		 * @brief Deallocate memory used by the list.
		 * 
		 * Note that this does not deallocate data items - that
		 * must be done manually.
		 */
		~List () throw ()
		{
			ListNode<C> *node = _root, *next;
			while (node)
			{
				next = node->next;
				delete node;
				node = next;
			}
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
		append (C *value) throw ()
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
		 * @brief Searches the list for a particular pointer.
		 * 
		 * Note that this compares pointer addresses, not the value
		 * of whatever is being pointed to.
		 * 
		 * @return the list node containing the given key, or NULL
		 *         if the key was not found.
		 */
		const ListNode<C> *
		find (C *key) const throw ()
		{
			ListNode<C> *node = _root;
			while (node)
			{
				// Yes, this is meant to compare pointers
				if (node->value == key)
				{
					return node;
				}
				node = node->next;
			}

			return NULL;
		}

		/**
		 * @brief Returns the first node in the list.
		 * 
		 * @return the first node in the list, or NULL if the list is
		 *         empty.
		 */
		const ListNode<C> *
		root () const throw ()
		{
			return _root;
		}

		/**
		 * @brief Returns the size of the list.
		 * 
		 * @return the size of the list.
		 */
		int
		size () const throw ()
		{
			return _size;
		}

	private:
		ListNode<C> *_root;
		int _size;
	};
}

#endif /* COPPER_UTIL_LIST_HPP */
