/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:51:35 by aborboll          #+#    #+#             */
/*   Updated: 2022/04/05 16:31:38 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "./utility.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include <functional>
#include <math.h>
int LEFT = 2;
int RIGHT = 3;
int RED = 1;
int BLACK = 2;

namespace ft
{
	template <typename T> class node
	{
	  public:
		node *left;
		node *right;
		node *parent;
		T     data;
		int   color;

		node(const T &value)
		    : left(NULL), right(NULL), parent(NULL), data(value)
		{
			color = 0;
		};
		~node(){};

		int getSide()
		{
			if (parent == NULL)
				return 0;
			if (parent->left == this)
				return LEFT;
			return RIGHT;
		}

		node *getBrother()
		{
			if (parent == NULL)
				return NULL;
			if (parent->left == this)
				return parent->right;
			return parent->left;
		}

		node *getUncle()
		{
			if (parent == NULL)
				return NULL;
			if (parent->left == this)
				return parent->right;
			return parent->left;
		}

		node *getGrandparent()
		{
			if (parent == NULL)
				return NULL;
			return parent->parent;
		}
	};

	template <class Key, class T, class Compare, class Allocator>
	class red_black_tree
	{
	};
}; // namespace ft
#endif
