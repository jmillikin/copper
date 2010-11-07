// Copyright (C) 2006-2010 John Millikin <jmillikin@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef COPPER_LIST_HPP
#define COPPER_LIST_HPP

#include <cstddef>

namespace Copper
{

template <class C>
struct ListNode
{
	ListNode(C *value)
		: next(NULL)
		, value(value)
	{
	}
	
	ListNode *next;
	C *value;
};

template <class C>
class List
{
public:
	typedef bool(type_matcher)(const C *key, const void *data);
	
	List()
		: _root(NULL)
		, _size(0)
	{
	}
	
	List(const List &other)
		: _root(NULL)
		, _size(0)
	{
		extend(other);
	}
	
	List &operator=(const List &other)
	{
		clear();
		extend(other);
		return *this;
	}
	
	~List()
	{
		clear();
	}
	
	void append(C *value)
	{
		if (_root)
		{
			ListNode<C> *last = _root;
			while (last->next)
			{
				last = last->next;
			}
			
			last->next = new ListNode<C>(value);
		}
		
		else
		{
			_root = new ListNode<C>(value);
		}
		
		++_size;
	}
	
	const ListNode<C> *find
		( type_matcher *matches
		, const void *data
		) const
	{
		const ListNode<C> *node = NULL;
		while (each(&node))
		{
			if (matches(node->value, data))
			{ return node; }
		}
		
		return NULL;
	}
	
	List<C> filter(type_matcher *matches, const void *data) const
	{
		List<C> new_list;
		const ListNode<C> *node = NULL;
		while (each(&node))
		{
			if (matches(node->value, data))
			{
				new_list.append(node->value);
			}
		}
		
		return new_list;
	}
	
	const ListNode<C> *root() const
	{
		return _root;
	}
	
	std::size_t size() const
	{
		return _size;
	}
	
	void extend(const List<C> &other)
	{
		const ListNode<C> *node = NULL;
		while (other.each(&node))
		{ append(node->value); }
	}
	
	bool each(const ListNode<C> **node_ptr) const
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
			*node_ptr = root();
			return (*node_ptr != NULL);
		}
	}
	
private:
	void clear()
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

#endif
