/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:51:35 by aborboll          #+#    #+#             */
/*   Updated: 2022/02/28 17:39:28 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "type_traits.hpp"
#include <functional>
#define LEFT 2;
#define RIGHT 3;

namespace ft
{
	template <typename T> class Node
	{
	  public:
		Node *left;
		Node *right;
		Node *parent;
		T     data;
		bool  color;

		Node(const T &value)
		    : left(nullptr), right(nullptr), parent(nullptr), data(value)
		{
			color = 0;
		};
		~Node(){};

		int getSide()
		{
			if (parent == nullptr)
				return 0;
			if (parent->left == this)
				return LEFT;
			return RIGHT;
		}

		Node *getBrother()
		{
			if (parent == nullptr)
				return nullptr;
			if (parent->left == this)
				return parent->right;
			return parent->left;
		}

		Node *getUncle()
		{
			if (parent == nullptr)
				return nullptr;
			if (parent->left == this)
				return parent->right;
			return parent->left;
		}

		Node *getGrandparent()
		{
			if (parent == nullptr)
				return nullptr;
			return parent->parent;
		}
	};
}; // namespace ft
#endif
