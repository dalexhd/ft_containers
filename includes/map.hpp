/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:09 by aborboll          #+#    #+#             */
/*   Updated: 2022/03/02 15:16:37 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

#include "iterator.hpp"
#include "tree.hpp"
#include "utility.hpp"
#include <functional>
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
		typedef Key                                   key_type;
		typedef T                                     mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;

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

	  public:
		ft::pair<iterator, bool> insert(const value_type &value)
		{
			return (_tree.insert(value));
		}
	};
} // namespace ft

#endif
