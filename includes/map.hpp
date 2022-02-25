/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:09 by aborboll          #+#    #+#             */
/*   Updated: 2022/02/25 15:12:47 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

#include "iterator.hpp"
#include "utility.hpp"
#include <functional>
#include <map>

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		typedef Key                                    key_type;
		typedef T                                      mapped_type;
		typedef ft::pair<const Key, T>                 value_type;
		typedef size_t                                 size_type;
		typedef ptrdiff_t                              difference_type;
		typedef Compare                                key_compare;
		typedef Allocator                              allocator_type;
		typedef value_type &                           reference;
		typedef const value_type &                     const_reference;
		typedef typename allocator_type::pointer       pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::iterator<pointer>         iterator;
		typedef typename ft::iterator<const_pointer>   const_iterator;
		// typedef map_iterator<typename iterator>             iterator;
		// typedef map_const_iterator<typename const_iterator> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<iterator> const_reverse_iterator;
	};
} // namespace ft

#endif
