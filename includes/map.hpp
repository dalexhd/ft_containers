/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:09 by aborboll          #+#    #+#             */
/*   Updated: 2022/04/07 16:16:14 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

#include "tree.hpp"
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
		map(const map &other) : _tree(other._tree){};
		// Destructor
		~map(){};

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
					return it;
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
					return it;
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
					return it;
				it++;
			}
			return end();
		};

	  public:
		void clear()
		{
			_tree.clear();
		}
		size_type count(const key_type &k) const
		{
			return (_tree.count(k));
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
			_tree.erase(position);
		}
		size_type erase(const key_type &k)
		{
			return (_tree.erase(k));
		}
		void erase(iterator first, iterator last)
		{
			_tree.erase(first, last);
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
			return (_tree.insert(position, val));
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			_tree.insert(first, last);
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
		map const &operator=(const map &x)
		{
			_tree = x._tree;
			return (*this);
		}

		mapped_type &operator[](const key_type &k)
		{
			return (insert(value_type(k, mapped_type())).first->second);
		}

	  public:
		void print(void)
		{
			_tree.print_tree();
		};
	};
	template <class Key, class Value, class Compare, class Alloc>
	bool operator==(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs);

	template <class Key, class Value, class Compare, class Alloc>
	bool operator!=(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs);

	template <class Key, class Value, class Compare, class Alloc>
	bool operator<(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs);

	template <class Key, class Value, class Compare, class Alloc>
	bool operator<=(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs);

	template <class Key, class Value, class Compare, class Alloc>
	bool operator>(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs);

	template <class Key, class Value, class Compare, class Alloc>
	bool operator>=(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y);
}; // namespace ft

#endif
