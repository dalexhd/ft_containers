/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:09 by aborboll          #+#    #+#             */
/*   Updated: 2022/04/05 15:31:10 by aborboll         ###   ########.fr       */
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
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	  public:
		typedef Key                    key_type;
		typedef T                      mapped_type;
		typedef ft::pair<const Key, T> value_type;

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
		typedef ft::node<value_type>                     node_type;
		typedef node_type *                              node_pointer;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef val_compare                              value_compare;
		typedef red_black_tree<Key, value_type, val_compare, Allocator> tree_type;
		typedef typename tree_type::iterator               iterator;
		typedef typename tree_type::const_iterator         const_iterator;
		typedef typename tree_type::reverse_iterator       reverse_iterator;
		typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

	  private:
		tree_type      _tree;
		allocator_type _allocator;
		key_compare    _comp;

	  public:
		explicit map(const Compare &comp = Compare(), const Allocator &alloc = Allocator())
		    : _tree(tree_type(comp, alloc)), _allocator(alloc), _comp(comp){};
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		    : _tree(tree_type(first, last, comp, alloc)), _allocator(alloc), _comp(comp){};

		map(const map &other) : _tree(other._tree){};

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
			iterator it = begin();
			while (it != end())
			{
				if (!_comp(it->first, k))
					return it;
				it++;
			}
			return end();
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
		iterator       upper_bound(const key_type &k);
		const_iterator upper_bound(const key_type &k) const;

	  public:
		void                                     clear();
		size_type                                count(const key_type &k) const;
		bool                                     empty() const;
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
		ft::pair<iterator, iterator>             equal_range(const key_type &k);
		void                                     erase(iterator position);
		size_type                                erase(const key_type &k);
		void     erase(iterator first, iterator last);
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
			return (_tree.insert(value));
		}
		iterator insert(iterator position, const value_type &val)
		{
			_tree.insert(position, val);
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			_tree.insert(first, last);
		}
		key_compare key_comp() const;
		size_type   max_size() const
		{
			return (_tree.max_size());
		}
		size_type size(void) const
		{
			return (_tree.size());
		}
		void          swap(map &x);
		value_compare value_comp() const;

	  public:
		map const &operator=(const map &x)
		{
			_tree = x._tree;
			return (*this);
		}
		mapped_type &operator[](const key_type &k)
		{
			return (
			    ((_tree.insert(ft::make_pair(k, mapped_type()))).first)->data.second); // a reference to the mapped type of a pair(key, mapped_type()), or of an existing key if one already existed
		}

	  public:
		void print(void)
		{
			_tree.print_tree();
		};
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y);

}; // namespace ft

#endif
