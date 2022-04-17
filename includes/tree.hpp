/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:51:35 by aborboll          #+#    #+#             */
/*   Updated: 2022/04/17 15:43:25 by aborboll         ###   ########.fr       */
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
	template <typename Value> class node
	{
	  public:
		node *left;
		node *right;
		node *parent;
		Value data;
		int   color;

		node() : left(NULL), right(NULL), parent(NULL), data(Value())
		{
			color = 0;
		};

		node(const Value &value)
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

	template <class Key, class Value, class Compare, class Allocator>
	class red_black_tree
	{
		template <bool isConst> class red_black_tree_iterator
		{
		  public:
			typedef ft::pair<const Key, Value> pair_type;
			typedef typename ft::conditional<isConst, const Key, Value>::type value_type;
			typedef typename ft::conditional<isConst, const node<Value>, node<Value> >::type node_type;
			typedef std::ptrdiff_t difference_type;
			typedef size_t         size_type;
			typedef typename ft::conditional<isConst, const Value *, Value *>::type pointer;
			typedef typename ft::conditional<isConst, const Value &, Value &>::type reference;

		  private:
			node_type *_ptr;

		  public:
			node_type *getPtr(void) const
			{
				return (_ptr);
			};

		  public:
			red_black_tree_iterator() : _ptr(NULL){};
			red_black_tree_iterator(node_type *ptr)
			    : _ptr(static_cast<node_type *>(ptr)){};
			template <bool _isConst>
			red_black_tree_iterator(const red_black_tree_iterator<_isConst> &x, typename ft::enable_if<!_isConst>::type * = 0)
			{
				_ptr = x.getPtr();
			}
			~red_black_tree_iterator(){};
			template <bool _isConst>
			red_black_tree_iterator &operator=(const red_black_tree_iterator<_isConst> &x)
			{
				_ptr = x.getPtr();
				return (*this);
			};
			template <bool _isConst>
			bool operator==(const red_black_tree_iterator<_isConst> &x) const
			{
				return (_ptr == x.getPtr());
			};
			template <bool _isConst>
			bool operator!=(const red_black_tree_iterator<_isConst> &x) const
			{
				return (!operator==(x));
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
				++(*this);
				return (iterator);
			};
			red_black_tree_iterator operator--(int)
			{
				red_black_tree_iterator iterator(*this);
				prev();
				return (iterator);
			};
			reference operator*(void)
			{
				return (_ptr->data);
			};

			reference &operator*(void) const
			{
				return (_ptr->data);
			};

			pointer operator->(void) const
			{
				return (&(_ptr->data));
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
		typedef Value     value_type;
		typedef Compare   value_compare;
		typedef Allocator allocator_type;
		typedef typename Allocator::template rebind<node<Value> >::other node_allocator;
		typedef typename node_allocator::pointer         node_pointer;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef std::ptrdiff_t                           difference_type;
		typedef std::size_t                              size_type;
		typedef red_black_tree_iterator<false>           iterator;
		typedef red_black_tree_iterator<true>            const_iterator;
		typedef ft::reverse_iterator<iterator>           reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

	  private:
		allocator_type _allocator; // Allocator used to allocate memory for the nodes
		node_allocator _node_allocator; // Allocator used to allocate the nodes
		value_compare  _comp;           // Comparator used to compare the values
		node_pointer   _root;           // Root node of the tree
		size_type      _size;           // Number of nodes in the tree

		node_pointer _start; // First node after sort.
		node_pointer _end;   // First node after sort.

		ft::node<Value> _trash; // Trash

	  public:
		// Default constructor
		red_black_tree()
		    : _allocator(allocator_type()), _comp(value_compare()), _root(NULL), _size(0){};
		// Constructor with a comparator
		red_black_tree(const value_compare &comp)
		    : _comp(comp), _root(NULL), _size(0){};
		// Constructor with an allocator
		red_black_tree(const allocator_type &alloc = node_allocator())
		    : _allocator(alloc), _comp(value_compare()), _root(NULL), _size(0), _start(&_trash), _end(&_trash){};
		// Constructor with a comparator and an allocator
		red_black_tree(const value_compare &comp, const allocator_type &alloc = node_allocator())
		    : _allocator(alloc), _comp(comp), _root(NULL), _size(0), _start(&_trash), _end(&_trash){};
		template <class InputIterator>
		red_black_tree(InputIterator first, InputIterator last, const value_compare &comp = value_compare(), const allocator_type &alloc = node_allocator())
		    : _allocator(alloc), _comp(comp), _root(NULL), _size(0)
		{
			insert(first, last);
		};
		// Copy constructor
		red_black_tree(const red_black_tree &tree)
		    : _allocator(tree._allocator), _comp(tree._comp)
		{
			for (const_iterator it = tree.begin(); it != tree.end(); ++it)
				insert(*it);
		};

		// Other
		/* 		red_black_tree operator=(const red_black_tree &tree)
		        {
		            clear();
		            insert(tree.begin(), tree.end());
		            return (*this);
		        }; */

		void clear(node_pointer node)
		{
			if (node)
			{
				clear(node->left);
				clear(node->right);
				_node_allocator.destroy(node);
				_node_allocator.deallocate(node, 1);
			}
		};

		void clear(void)
		{
			clear(_root);
			_size = 0;
			_root = NULL;
			_start = _end;
		};

		// Destructor
		~red_black_tree()
		{
			clear(_root);
		};

	  private:
		node_pointer min(node_pointer node) const
		{
			node_pointer tmp = node;

			while (tmp->left)
				tmp = tmp->left;
			return (tmp);
		}

		node_pointer max(node_pointer node) const
		{
			node_pointer tmp = node;

			while (tmp->right)
				tmp = tmp->right;
			return (tmp->right);
		}

	  public:
		// Iterators
		iterator begin(void)
		{
			return (iterator(_start));
		};
		iterator end(void)
		{
			return (iterator(_end));
		};
		const_iterator begin(void) const
		{
			return (const_iterator(_start));
		};
		const_iterator end(void) const
		{
			return (const_iterator(_end));
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
		// Tree main functions
		size_type size(void) const
		{
			return (_size);
		};

		value_compare value_comp(void) const
		{
			return (_comp);
		};

		size_type max_size(void) const
		{
			return (_node_allocator.max_size());
		};

		bool empty(void) const
		{
			return (_size == 0);
		};

		allocator_type get_allocator(void) const
		{
			return (_node_allocator);
		};

		node_pointer create_node(const value_type &value)
		{
			node_pointer node = _node_allocator.allocate(1);
			_node_allocator.construct(node, value);
			return (node);
		}

		node_pointer delete_node(const value_type &key)
		{
			node_pointer node = search(key);
			if (node)
			{
				node_pointer parent = node->parent;
				if (node->left && node->right)
				{
					node_pointer min_node = min(node->right);
					node = min_node;
					parent = node->parent;
				}
				if (node->left)
					node->left->parent = node->parent;
				if (node->right)
					node->right->parent = node->parent;
				if (node->parent)
				{
					if (node->parent->left == node)
						node->parent->left = node->left ? node->left : node->right;
					else
						node->parent->right = node->left ? node->left : node->right;
				}
				else
					_root = node->left ? node->left : node->right;
				_node_allocator.destroy(node);
				_node_allocator.deallocate(node, 1);
				_start = min(_root);
				_end = max(_root);
				--_size;
			}
			return (NULL);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				insert(*first);
		}

		node_pointer insert(node_pointer parent, node_pointer node)
		{
			node_pointer tmp = parent;
			while (tmp) // Here we go down the tree until we find a node that is NULL
			{
				parent = tmp;
				if (_comp(node->data, tmp->data))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			if (_comp(node->data, parent->data)) // Check if the node is the left child of its parent
				parent->left = node;
			else
				parent->right = node;
			node->parent = parent;
			node->left = node->right = NULL;
			node->color = RED; // INFO: check if this is red
			fix_insert(node);
			_start = min(_root);
			_end = max(_root);
			return (node);
		}
		node_pointer insert(node_pointer node)
		{
			if (!_root)
			{
				_root = node;
				_root->color = BLACK;
				_root->left = _root->right = NULL;
				_root->parent = NULL;
				_start = _root;
				_end = _root;
			}
			else
			{
				insert(_root, node);
			}
			return (node);
		}

		node_pointer search(node_pointer node, const Value &value) const
		{
			while (node)
			{
				if (_comp(value, node->data))
					node = node->left;
				else if (_comp(node->data, value))
					node = node->right;
				else
					return (node);
			}
			return (NULL);
		}
		node_pointer search(const Value &value) const
		{
			return (search(_root, value));
		}
		const_iterator find(const value_type &value) const
		{
			return (const_iterator(search(value)));
		}
		iterator find(const value_type &value)
		{
			return (iterator(search(value)));
		}

		ft::pair<iterator, bool> insert(const value_type &value)
		{
			node_pointer node = search(value);
			if (node)
				return (ft::pair<iterator, bool>(iterator(node), false));
			node = create_node(value);
			node->right = node->left = NULL;
			insert(node);
			_size++;
			ft::pair<iterator, bool> ret(iterator(node), true);
			return (ret);
		}

		ft::pair<iterator, bool> insert(const value_type &key, const Value &value)
		{
			node_pointer node = search(key);
			if (node)
				return (ft::pair<iterator, bool>(iterator(node), false));
			node = create_node(key, value);
			node->right = node->left = NULL;
			insert(node);
			_size++;
			ft::pair<iterator, bool> ret(iterator(node), true);
			return (ret);
		}

		iterator insert(iterator position, const value_type &value)
		{
			node_pointer node = search(value);
			if (node)
				return (iterator(node));
			node = create_node(value);
			node->right = node->left = NULL;
			if (position == begin()) // If the iterator is at the beginning of the tree
			{
				clear();
				node->parent = NULL;
				_root = node;
			}
			else if (position == end()) // If the iterator is at the end of the tree
			{
				node->parent = _root;
				insert(node);
			}
			else // If the iterator is somewhere in the middle of the tree
				insert(node);
			_size++;
			return (iterator(node));
		}

		void swap(red_black_tree &x)
		{
			std::swap(_root, x._root);
			std::swap(_size, x._size);
			std::swap(_start, x._start);
			std::swap(_end, x._end);
			std::swap(_comp, x._comp);
			std::swap(_node_allocator, x._node_allocator);
		}

		void rotate_left(node_pointer node)
		{
			node_pointer tmp = node->right;
			node->right = tmp->left;
			if (tmp->left)
				tmp->left->parent = node;
			tmp->parent = node->parent;
			if (!node->parent)
				_root = tmp;
			else if (node == node->parent->left)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			tmp->left = node;
			node->parent = tmp;
		}

		void rotate_right(node_pointer node)
		{
			node_pointer tmp = node->left;
			node->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = node;
			tmp->parent = node->parent;
			if (!node->parent)
				_root = tmp;
			else if (node == node->parent->left)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			tmp->right = node;
			node->parent = tmp;
		}

		/**
		 * @brief Fix insert
		 * @see https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
		 * @param node
		 */
		void fix_insert(node_pointer node) // here we fix the tree after insertion.
		{
			while (node->parent && node->parent->color == RED)
			{
				if (node->parent == node->parent->parent->left) // If the parent is the left child of the grandparent
				{
					node_pointer uncle = node->parent->parent->right;
					if (uncle && uncle->color == RED) // If the uncle is red
					{
						node->parent->color = BLACK;
						uncle->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->right) // If the node is the right child of its parent
						{
							node = node->parent;
							rotate_left(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						rotate_right(node->parent->parent);
					}
				}
				else
				{
					node_pointer uncle = node->parent->parent->left;
					if (uncle && uncle->color == RED) // If the parent is the right child of the grandparent
					{
						node->parent->color = BLACK;
						uncle->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->left) // If the node is the left child of its parent
						{
							node = node->parent;
							rotate_right(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						rotate_left(node->parent->parent);
					}
				}
			}
			_root->color = BLACK;
		}

		// create a function that prints the tree
		void print_tree(node_pointer node, int space) const
		{
			if (node == NULL)
				return;
			space += 10;
			print_tree(node->right, space);
			std::cout << std::endl;
			for (int i = 10; i < space; i++)
				std::cout << " ";
			std::cout << node->data.first << std::endl;
			print_tree(node->left, space);
		}

		void print_tree(void) const
		{
			print_tree(_root, 0);
			std::cout << ".----------------------------------." << std::endl;
		}

		node_pointer getRoot()
		{
			return _root;
		}

	  public:
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type)
		{
			for (; first != last; first++)
				insert(*first);
		}
	};
}; // namespace ft
#endif
