/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:51:35 by aborboll          #+#    #+#             */
/*   Updated: 2022/03/02 13:49:35 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "./utility.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include <functional>
#define LEFT 2;
#define RIGHT 3;

namespace ft
{
	template <typename T> class node
	{
	  public:
		node *left;
		node *right;
		node *parent;
		T     data;
		bool  color;

		node(const T &value)
		    : left(nullptr), right(nullptr), parent(nullptr), data(value)
		{
			color = 0;
		};
		~node(){};

		int getSide()
		{
			if (parent == nullptr)
				return 0;
			if (parent->left == this)
				return LEFT;
			return RIGHT;
		}

		node *getBrother()
		{
			if (parent == nullptr)
				return nullptr;
			if (parent->left == this)
				return parent->right;
			return parent->left;
		}

		node *getUncle()
		{
			if (parent == nullptr)
				return nullptr;
			if (parent->left == this)
				return parent->right;
			return parent->left;
		}

		node *getGrandparent()
		{
			if (parent == nullptr)
				return nullptr;
			return parent->parent;
		}
	};

	template <class Key, class T, class Compare, class Allocator>
	class red_black_tree
	{
		template <bool isConst = false> class red_black_tree_iterator
		{
		  public:
			typedef ft::pair<const Key, T> pair_type;
			typedef typename ft::conditional<isConst, const pair_type, pair_type>::type value_type;
			typedef typename ft::conditional<isConst, const node<T>, node<T> >::type node_type;
			typedef std::ptrdiff_t difference_type;
			typedef size_t         size_type;

		  private:
			node_type *_ptr;

		  public:
			node_type *getPtr(void)
			{
				return (_ptr);
			};

		  public:
			red_black_tree_iterator() : _ptr(NULL){};
			red_black_tree_iterator(const node_type *ptr) : _ptr(ptr){};
			template <bool _isConst>
			red_black_tree_iterator(const red_black_tree_iterator<_isConst> &x, typename ft::enable_if<!_isConst>::type * = 0)
			{
				_ptr = x.getPtr();
			}
			~red_black_tree_iterator(){};
			red_black_tree_iterator &operator=(const red_black_tree_iterator &x)
			{
				_ptr = x.getPtr();
			};
			template <bool _isConst>
			bool operator==(const red_black_tree_iterator<_isConst> &x)
			{
				_ptr == x.getPtr();
			};
			template <bool _isConst>
			bool operator!=(const red_black_tree_iterator<_isConst> &x)
			{
				!(_ptr == x.getPtr());
			};
			red_black_tree_iterator &operator++(void)
			{
				next();
				return (*this);
			};
			red_black_tree_iterator &operator--(void)
			{
				prev();
				return (*this);
			}
			red_black_tree_iterator operator++(int)
			{
				red_black_tree_iterator iterator(*this);
				next();
				return (iterator);
			};
			red_black_tree_iterator operator--(int)
			{
				red_black_tree_iterator iterator(*this);
				prev();
				return (iterator);
			};
			value_type &operator*(void) const
			{
				return (_ptr->data);
			};
			value_type *operator->(void) const
			{
				return (&_ptr);
			};
			void next(void)
			{
				if (_ptr->right)
				{
					_ptr = _ptr->right;
					while (_ptr->left) // Here we go to the left most node of the right subtree
						_ptr = _ptr->left;
				}
				else
				{
					node_type *tmp = _ptr->parent;
					while (tmp && _ptr == tmp->right) // Here we check if the node is the right child of its parent and go up until we find a node that is the left child of its parent
					{
						_ptr = tmp;
						tmp = tmp->parent;
					}
					_ptr = tmp;
				}
			};
			void prev(void)
			{
				if (_ptr->left)
				{
					_ptr = _ptr->left;
					while (_ptr->right) // Here we go to the right most node of the left subtree
						_ptr = _ptr->right;
				}
				else
				{
					node_type *tmp = _ptr->parent;
					while (tmp && _ptr == tmp->left) // Here we check if the node is the left child of its parent and go up until we find a node that is the right child of its parent
					{
						_ptr = tmp;
						tmp = tmp->parent;
					}
					_ptr = tmp;
				}
			};
			void next(size_t n)
			{
				for (size_t i = 0; i < n; i++)
					next();
			};
			void prev(size_t n)
			{
				for (size_t i = 0; i < n; i++)
					prev();
			};
		};

	  public:
		typedef T         value_type;
		typedef Compare   value_compare;
		typedef Allocator allocator_type;
		typedef typename Allocator::template rebind<node<T> >::other node_allocator;
		typedef typename node_allocator::pointer         node_pointer;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef std::ptrdiff_t                           difference_type;
		typedef std::size_t                              size_type;
		typedef red_black_tree_iterator<>                iterator;
		typedef red_black_tree_iterator<true>            const_iterator;
		typedef ft::reverse_iterator<iterator>           reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

	  private:
		allocator_type _allocator; // Allocator used to allocate the nodes
		value_compare  _comp;      // Comparator used to compare the values
		node_pointer   _root;      // Root node of the tree
		size_type      _size;      // Number of nodes in the tree

	  public:
		// Default constructor
		red_black_tree()
		    : _allocator(allocator_type()), _comp(value_compare()), _root(NULL), _size(0){};
		// Constructor with a comparator
		red_black_tree(const value_compare &comp)
		    : _comp(comp), _root(NULL), _size(0){};
		// Constructor with an allocator
		red_black_tree(const allocator_type &alloc = node_allocator())
		    : _allocator(alloc), _comp(value_compare()), _root(NULL), _size(0){};
		// Constructor with a comparator and an allocator
		red_black_tree(const value_compare &comp, const allocator_type &alloc = node_allocator())
		    : _allocator(alloc), _comp(comp), _root(NULL), _size(0){};
		// Copy constructor
		red_black_tree(const red_black_tree &tree)
		    : _comp(tree._comp), _root(tree._root), _allocator(tree._allocator), _size(tree._size)
		{
			*this = tree;
		};
		// Assignment operator
		red_black_tree operator=(const red_black_tree &tree)
		{
			(void) tree;
		};
		// Destructor
		~red_black_tree(){};

	  public:
		// Iterators
		iterator begin(void)
		{
			return (iterator(_root));
		};
		iterator end(void)
		{
			return (iterator(_root));
		};
		const_iterator begin(void) const
		{
			return (const_iterator(_root));
		};
		const_iterator end(void) const
		{
			return (const_iterator(_root));
		};
		reverse_iterator rbegin(void)
		{
			return (reverse_iterator(end()));
		};
		reverse_iterator rend(void)
		{
			return (reverse_iterator(begin()));
		};
		const_reverse_iterator rbegin(void) const
		{
			return (const_reverse_iterator(end()));
		};
		const_reverse_iterator rend(void) const
		{
			return (const_reverse_iterator(begin()));
		};

	  public:
		// Tree functions
		size_type size(void) const
		{
			return (_size);
		};
		bool empty(void) const
		{
			return (_size == 0);
		};
		allocator_type get_allocator(void) const
		{
			return (_allocator);
		};
		// Tree main functions
		node_pointer insert(node_pointer parent, node_pointer node)
		{
			node_pointer tmp = parent;
			while (tmp) // Here we go down the tree until we find a node that is NULL
			{
				parent = tmp;
				if (_comp(node->value, tmp->value))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			if (_comp(node->value, parent->value)) // Chekc if the node is the left child of its parent
				parent->left = node;
			else
				parent->right = node;
			node->parent = parent;
		}
		node_pointer insert(node_pointer node)
		{
			if (!_root) // If the tree is empty
				return (node);
			insert(_root, node);
			return (node);
		}
	};
}; // namespace ft
#endif