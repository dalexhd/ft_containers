/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 00:04:49 by aborboll          #+#    #+#             */
/*   Updated: 2022/02/16 19:23:10 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "vector.hpp"
#include <functional>
#include <queue>

namespace ft
{
	template <class T1, class T2> struct pair
	{
	  public:
		// Member types
		typedef T1 first_type;  // The first template parameter (T1)
		typedef T2 second_type; // The second template parameter (T2)

		// Member variables
		first_type  first;  // The first value in the pair
		second_type second; // The second value in the pair

		/**
		 * @brief Default constructor.
		 * Constructs a pair object with its elements value-initialized.
		 *
		 */
		pair() : first(), second(){};

		/**
		 * @brief Copy / move constructor (and implicit conversion)
		 * The object is initialized with the contents of the pr pair object.
		 * The corresponding member of pr is passed to the constructor of each of its members.
		 *
		 * @tparam U The first template parameter
		 * @tparam V The second template parameter (T2)
		 * @param pr Another pair object. This may be an object of the same type as the object being constructed or of a pair type whose elements' types are implicitly convertible to those in the pair being constructed.
		 */
		template <class U, class V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second){};

		/**
		 * @brief Initialization constructor.
		 * Member first is constructed with a and member second with b.
		 *
		 * @param a An object of the type of first, or some other type implicitly convertible to it.
		 * @param b An object of the type of second, or some other type implicitly convertible to it.
		 */
		pair(const first_type &a, const second_type &b) : first(a), second(b){};

		/**
		 * @brief Assigns pr as the new content for the pair object.
		 * Member first is assigned pr.first, and member second is assigned pr.second.
		 * The copying forms (1) perform copy assignments, with the elements of its argument preserving their values after the call. While the moving forms (2) perform move assignments (as if calling forward for each element), which, for elements of types supporting move semantics implies that these elements of pr are left in an unspecified but valid state.
		 *
		 * @param pr Another pair object.
		 * This may be an object of the same type or of a pair type whose elements' types are implicitly convertible.
		 * @return pair& *this
		 */
		template <class U, class V> pair &operator=(const pair<U, V> &pr)
		{
			if (pr == *this)
				return (*this);
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs < rhs));
	}

	/**
	 * fn:	make_pair
	 * url: https://en.cppreference.com/w/cpp/utility/pair/make_pair
	 *
	 * @brief Creates a std::pair object, deducing the target type from the types of arguments.
	 */
	template <class T1, class T2> ft::pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return (ft::pair<T1, T2>(t, u));
	};

	// Red-Black tree utility
	enum Color
	{
		RED,
		BLACK
	};

	struct Node
	{
		int   data;
		bool  color;
		Node *left;
		Node *right;
		Node *parent;
		Node(int data)
		{
			this->data = data;
			left = right = parent = NULL;
			this->color = RED;
		}
	};

	class red_black_tree
	{
	  private:
		Node *_root;
		Node *_insert(Node *root, Node *parent)
		{
			if (root == NULL)
				return parent;
			if (parent->data < root->data)
			{
				root->left = _insert(root->left, parent);
				root->left->parent = root;
			}
			else if (parent->data > root->data)
			{
				root->right = _insert(root->right, parent);
				root->right->parent = root;
			}
			return (root);
		};

	  protected:
		void rotateLeft(Node *&root, Node *&parent)
		{
			Node *pt_right = parent->right;

			parent->right = pt_right->left;
			if (parent->right != NULL)
				parent->right->parent = parent;
			pt_right->parent = parent->parent;
			if (parent->parent == NULL)
				root = pt_right;
			else if (parent == parent->parent->left)
				parent->parent->left = pt_right;
			else
				parent->parent->right = pt_right;
			pt_right->left = parent;
			parent->parent = pt_right;
		};
		void rotateRight(Node *&root, Node *&parent)
		{
			Node *pt_left = parent->left;

			parent->left = pt_left->right;
			if (parent->left != NULL)
				parent->left->parent = parent;
			pt_left->parent = parent->parent;
			if (parent->parent == NULL)
				root = pt_left;
			else if (parent == parent->parent->left)
				parent->parent->left = pt_left;
			else
				parent->parent->right = pt_left;
			pt_left->right = parent;
			parent->parent = pt_left;
		};
		void fixViolation(Node *&root, Node *&parent)
		{
			Node *parent_pt = NULL;
			Node *grand_parent_pt = NULL;

			while (parent != root && parent->color != BLACK && parent->parent->color == RED)
			{
				parent_pt = parent->parent;
				grand_parent_pt = parent->parent->parent;

				if (parent_pt == grand_parent_pt->left)
				{
					Node *uncle_pt = grand_parent_pt->right;

					if (uncle_pt != NULL && uncle_pt->color == RED)
					{
						grand_parent_pt->color = RED;
						parent_pt->color = BLACK;
						uncle_pt->color = BLACK;
						parent = grand_parent_pt;
					}
					else
					{
						if (parent == parent_pt->right)
						{
							rotateLeft(root, parent_pt);
							parent = parent_pt;
							parent_pt = parent->parent;
						}
						rotateRight(root, grand_parent_pt);
						std::swap(parent_pt->color, grand_parent_pt->color);
						parent = parent_pt;
					}
				}
				else
				{
					Node *uncle_pt = grand_parent_pt->left;

					if (uncle_pt != NULL && uncle_pt->color == RED)
					{
						grand_parent_pt->color = RED;
						parent_pt->color = BLACK;
						uncle_pt->color = BLACK;
						parent = grand_parent_pt;
					}
					else
					{
						if (parent == parent_pt->left)
						{
							rotateLeft(root, parent_pt);
							parent = parent_pt;
							parent_pt = parent->parent;
						}
						rotateLeft(root, grand_parent_pt);
						std::swap(parent_pt->color, grand_parent_pt->color);
						parent = parent_pt;
					}
				}
			}
			root->color = BLACK;
		};

	  public:
		red_black_tree() : _root(NULL){};
		void insert(const int &n)
		{
			Node *parent = new Node(n);
			_root = _insert(_root, parent);
			fixViolation(_root, parent);
		};
		void inOrder(Node *root)
		{
			if (root == NULL)
				return;
			inOrder(root->left);
			std::cout << root->data << "  ";
			inOrder(root->right);
		};
		void levelOrder()
		{
			if (_root == NULL)
				return;
			std::queue<Node *> q;
			q.push(_root);
			while (!q.empty())
			{
				Node *temp = q.front();
				std::cout << temp->data << "  ";
				q.pop();
				if (temp->left != NULL)
					q.push(temp->left);
				if (temp->right != NULL)
					q.push(temp->right);
			}
		};

		Node *getRoot()
		{
			return (_root);
		}
	};
} // namespace ft

#endif
