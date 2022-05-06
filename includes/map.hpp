/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:09 by aborboll          #+#    #+#             */
/*   Updated: 2022/05/06 07:45:58 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

#include "tree.hpp"
#include "vector.hpp"
#include <map>

namespace ft
{
	/*
	 ** MAP
	 */
	template <typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, Value> > >
	class map
	{
	  public:
		typedef Key                        key_type;
		typedef Value                      mapped_type;
		typedef ft::pair<const Key, Value> value_type;

	  private:
		class val_compare
		{
		  private:
			Compare _comp;

		  public:
			val_compare(Compare comp) : _comp(comp)
			{
			}
			bool operator()(const value_type &lhs, const value_type &rhs) const
			{
				return (_comp(lhs.first, rhs.first));
			}
		};

	  public:
		typedef Compare                                  key_compare;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef val_compare                              value_compare;
		typedef red_black_tree<key_type, value_type, value_compare, Allocator> rb_tree;
		typedef node<value_type>                         _node;
		typedef typename rb_tree::iterator               iterator;
		typedef typename rb_tree::const_iterator         const_iterator;
		typedef typename rb_tree::reverse_iterator       reverse_iterator;
		typedef typename rb_tree::const_reverse_iterator const_reverse_iterator;

	  private:
		rb_tree        _tree;
		allocator_type _allocator;
		key_compare    _comp;

	  public:
		// Default constructor
		explicit map(const Compare &comp = Compare(), const Allocator &alloc = Allocator())
		    : _tree(rb_tree(comp, alloc)), _allocator(alloc), _comp(comp){};
		// Range constructor
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		    : _tree(rb_tree(first, last, comp, alloc)), _allocator(alloc), _comp(comp){};
		// Copy constructor
		map(const map &other)
		    : _tree(other._tree), _allocator(other._allocator), _comp(other._comp){};
		// Destructor
		~map(){
		    //_tree.clear();
		};

	  public:
		// Iterators
		iterator begin()
		{
			return (_tree.begin());
		}
		const_iterator begin() const
		{
			return (_tree.begin());
		}
		iterator end()
		{
			return (_tree.end());
		}
		const_iterator end() const
		{
			return (const_iterator(_tree.end()));
		}
		reverse_iterator rbegin()
		{
			return (_tree.rbegin());
		}
		const_reverse_iterator rbegin() const
		{
			return (_tree.rbegin());
		}
		reverse_iterator rend()
		{
			return (_tree.rend());
		}
		const_reverse_iterator rend() const
		{
			return (_tree.rend());
		}
		iterator lower_bound(const key_type &k)
		{
			iterator it = begin();
			while (it != end())
			{
				if (!_comp(it->first, k))
					return (it);
				it++;
			}
			return begin();
		}
		const_iterator lower_bound(const key_type &k) const
		{
			const_iterator it = begin();
			while (it != end())
			{
				if (!_comp(it->first, k))
					return (it);
				it++;
			}
			return end();
		}
		iterator upper_bound(const key_type &k)
		{
			iterator it = begin();
			while (it != end())
			{
				if (_comp(k, it->first))
					return it;
				it++;
			}
			return end();
		}

		const_iterator upper_bound(const key_type &k) const
		{
			const_iterator it = begin();
			while (it != end())
			{
				if (_comp(k, it->first))
					return (it);
				it++;
			}
			return end();
		};

	  public:
		void clear()
		{
			_tree.clear();
		}
		void reset()
		{
			_tree.reset();
		}
		size_type count(const key_type &k) const
		{
			size_type      n = 0;
			const_iterator it = begin();
			while (it != end())
			{
				if (!_comp(it->first, k) && !_comp(k, it->first))
					n++;
				it++;
			}
			return (n);
		}
		bool empty() const
		{
			return (_tree.empty());
		}
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}
		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		void erase(iterator position)
		{
			_node *ptr = position.getPtr();
			erase(ptr->data.first);
		}

		size_type erase(const key_type &k)
		{
			ft::node<value_type> *ptr = _tree.search(value_type(k, mapped_type()));
			if (ptr == NULL)
				return (0);
			_tree.delete_node(ptr);
			return (1);
		}

		void erase(iterator first, iterator last)
		{
			for (; first != last; first++)
				erase(first);
		}
		iterator find(const key_type &k)
		{
			return (iterator(_tree.find(value_type(k, mapped_type()))));
		}
		const_iterator find(const key_type &k) const
		{
			return (const_iterator(_tree.find(value_type(k, mapped_type()))));
		}
		allocator_type get_allocator() const
		{
			return (_tree.get_allocator());
		}
		ft::pair<iterator, bool> insert(const value_type &value)
		{
			ft::pair<typename rb_tree::iterator, bool> res = _tree.insert(value);
			return (ft::pair<iterator, bool>(iterator(res.first), res.second));
		}
		iterator insert(iterator position, const value_type &val)
		{
			(void) position;
			return (insert(val).first);
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL)
		{
			for (; first != last; first++)
				insert(*first);
		}
		key_compare key_comp() const
		{
			return (_comp);
		}
		size_type max_size() const
		{
			return (_tree.max_size());
		}
		size_type size() const
		{
			return (_tree.size());
		}
		void swap(map &x)
		{
			_tree.swap(x._tree);
		}
		value_compare value_comp() const
		{
			return (_tree.value_comp());
		}

	  public:
		map const &operator=(map &x)
		{
			if (this == &x)
				return (*this);
			reset();
			std::swap(_allocator, x._allocator);
			std::swap(_comp, x._comp);
			for (const_iterator it = x.begin(); it != x.end(); it++)
				this->insert(*it);
			return (*this);
		}

		mapped_type &operator[](const key_type &k)
		{
			if (_tree.find(value_type(k, mapped_type())) == _tree.end())
				return (insert(value_type(k, mapped_type())).first->second);
			return _tree.find(value_type(k, mapped_type()))->second;
		}

	  public:
		void print(void)
		{
			_tree.print_tree();
		};
	};
	template <class Key, class Value, class Compare, class Alloc>
	bool operator==(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename map<Key, Value, Compare, Alloc>::const_iterator it = lhs.begin();
		while (it != lhs.end())
		{
			if (rhs.find(it->first) == rhs.end())
				return (false);
			it++;
		}
		return (true);
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator!=(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator<(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator<=(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		return (!operator<(rhs, lhs));
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator>(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		return (operator<(rhs, lhs));
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator>=(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		return (!operator<(lhs, rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}
}; // namespace ft

#endif
