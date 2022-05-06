/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:51:35 by aborboll          #+#    #+#             */
/*   Updated: 2022/05/06 13:57:31 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "./vector.hpp"

int LEFT = 2;
int RIGHT = 3;
int RED = 1;
int BLACK = 2;
int D_BLACK = 3;

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

		node()
		    : left(NULL), right(NULL), parent(NULL), data(Value()), color(0){};

		node(const Value &value)
		    : left(NULL), right(NULL), parent(NULL), data(value), color(0){};

		node(const node &other, const Value &value)
		{
			left = other.left;
			right = other.right;
			parent = other.parent;
			data = value;
			color = other.color;
		};

		int getSide()
		{
			if (parent == NULL)
				return (0);
			if (parent->left == this)
				return (LEFT);
			return (RIGHT);
		}

		bool isLeft()
		{
			return (getSide() == LEFT);
		}

		bool isRight()
		{
			return (getSide() == RIGHT);
		}

		~node(){};
	};

	template <class Key, class Value, class Compare, class Allocator>
	class red_black_tree
	{
		template <bool isConst> class red_black_tree_iterator
		{
		  public:
			typedef ft::pair<const Key, Value> pair_type;
			typedef std::ptrdiff_t             difference_type;
			typedef size_t                     size_type;
			typedef typename ft::conditional<isConst, const Key, Value>::type value_type;
			typedef typename ft::conditional<isConst, const node<Value>, node<Value> >::type node_type;
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
			};

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
			};

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

			~red_black_tree_iterator(){};
		};

	  public:
		typedef Value                                value_type;
		typedef node<Value>                          node_type;
		typedef Compare                              value_compare;
		typedef Allocator                            allocator_type;
		typedef node_type                           *node_pointer;
		typedef std::size_t                          size_type;
		typedef red_black_tree_iterator<false>       iterator;
		typedef red_black_tree_iterator<true>        const_iterator;
		typedef ft::reverse_iterator<iterator>       reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		typedef typename Allocator::template rebind<node<Value> >::other node_allocator;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;

	  private:
		allocator_type _allocator; // Allocator used to allocate memory for the nodes
		node_allocator _node_allocator; // Allocator used to allocate the nodes
		value_compare  _comp;           // Comparator used to compare the values
		node_pointer   _root;           // Root node of the tree
		size_type      _size;           // Number of nodes in the tree

		node_pointer _start; // First node
		node_pointer _end;   // Last node of the tree.

		ft::vector<node_pointer> _pointers; // Vector used to store the pointers to the nodes

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
		// Default constructor
		red_black_tree()
		    : _allocator(allocator_type()), _comp(value_compare()), _root(NULL), _size(0), _start(NULL), _end(NULL)
		{
			_end = create_node(value_type(), D_BLACK);
		};

		// Constructor with a comparator
		red_black_tree(const value_compare &comp)
		    : _comp(comp), _root(NULL), _size(0), _start(NULL), _end(NULL){};

		// Constructor with an allocator
		red_black_tree(const allocator_type &alloc = node_allocator())
		    : _allocator(alloc), _comp(value_compare()), _root(NULL), _size(0), _start(NULL), _end(NULL)
		{
			_end = create_node(value_type(), D_BLACK);
		};

		// Constructor with a comparator and an allocator
		red_black_tree(const value_compare &comp, const allocator_type &alloc = node_allocator())
		    : _allocator(alloc), _comp(comp), _root(NULL), _size(0), _start(NULL), _end(NULL)
		{
			_end = create_node(value_type(), D_BLACK);
		};

		template <class InputIterator>
		red_black_tree(InputIterator first, InputIterator last, const value_compare &comp = value_compare(), const allocator_type &alloc = node_allocator())
		    : _allocator(alloc), _comp(comp), _root(NULL), _size(0)
		{
			_end = create_node(value_type(), D_BLACK);
			insert(first, last);
		};

		// Copy constructor
		red_black_tree(const red_black_tree &tree)
		    : _allocator(tree._allocator), _comp(tree._comp), _root(NULL), _size(0), _start(NULL), _end(NULL)
		{
			_end = create_node(value_type(), D_BLACK);
			for (const_iterator it = tree.begin(); it != tree.end(); ++it)
				insert(*it);
		};

		void clear(void)
		{
			for (size_t i = 0; i < _pointers.size(); i++)
			{
				_node_allocator.destroy(_pointers[i]);
				_node_allocator.deallocate(_pointers[i], 1);
			}
			_pointers.clear();
			_size = 0;
			_root = _start = _end = NULL;
		};

		void reset(void)
		{
			clear();
			_end = create_node(value_type(), D_BLACK);
		};

	  private:
		node_pointer min(node_pointer node) const
		{
			node_pointer tmp = node;

			while (tmp->left)
				tmp = tmp->left;
			return (tmp);
		};

		// CASE 1: It might happen that it's our last node in the tree. In this case we will need to set root to NULL.
		// CASE 2: If the node is located at last level of the tree, it will not have any descentants. This means that node left will be nil, and right might be eigther nil or double black. In case node is located at the left side, we will delete node's parent left node, and in case it's node's parent right, we will delete the right side.
		// CASE 3: If node right and node left != null and also node right is not d_black.
		// In this case, we'll first get the left most side of the node, and after we will swap it's data with the node data. After we will delete node by calling delete_node(left most side). This will trigger case 2.
		// Case 4: In case there is not left node, we will replace node with the node right value.
		// Case 5: Same as 4 but with right node.
		void delete_node_from_tree(node_pointer node)
		{
			// In case it's our last node of the tree
			if (!node->parent && !node->left && (!node->right || node->right->color == D_BLACK))
				_root = NULL;
			else if (!node->left && (!node->right || node->right->color == D_BLACK)) // In case it hasn't any descentants...
			{
				if (node->isLeft())
					node->parent->left = NULL;
				else
					node->parent->right = NULL;
			}
			else if (node->left && (node->right && node->right->color != D_BLACK)) // In case it has any descentants...
			{
				node_pointer tmp = min(node->right);
				swap(node, tmp);
				delete_node_from_tree(node);
			}
			else if (!node->left)
			{
				node->right->parent = node->parent;
				*get_parent_ptr(node) = node->right;
			}
			else if (!node->right || node->right->color == D_BLACK)
			{
				node->left->parent = node->parent;
				*get_parent_ptr(node) = node->left;
			}
			fixEndStart();
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

		allocator_type get_allocator(void) const
		{
			return (_node_allocator);
		};

		node_pointer create_node(const value_type &value)
		{
			node_pointer node = _node_allocator.allocate(1);
			_node_allocator.construct(node, value);
			_pointers.push_back(node);
			return (node);
		}

		node_pointer create_node(const value_type &value, int color)
		{
			node_pointer node = _node_allocator.allocate(1);
			_node_allocator.construct(node, value);
			node->color = color;
			_pointers.push_back(node);
			return (node);
		};

		void delete_fixup(node_pointer node)
		{
			if (node->parent)
			{
				node_pointer tmp;
				if (node == _root)
					tmp = NULL;
				else
					tmp = node->isLeft() ? node->parent->left : node->parent->right;
				if (tmp && tmp->color == RED)
				{
					node->parent->color = RED;
					tmp->color = D_BLACK;
					if (tmp->isLeft())
						rotate_left(node->parent);
					else
						rotate_right(node->parent);
				}
			}
		};

		void delete_node(node_pointer node)
		{
			if (!node)
				return;
			delete_node_from_tree(node);
			_size--;
		};

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				insert(*first);
		};

		node_pointer insert(node_pointer parent, node_pointer node)
		{
			if (parent == NULL || parent->color == D_BLACK)
				return node;
			if (_comp(node->data, parent->data))
			{
				parent->left = insert(parent->left, node);
				parent->left->parent = parent;
			}
			else if (!_comp(node->data, parent->data))
			{
				parent->right = insert(parent->right, node);
				parent->right->parent = parent;
			}
			return (parent);
		};

		void fixEndStart()
		{
			if (_root == NULL)
			{
				_start = _root;
				_end = _root;
				return;
			}
			node_pointer tmp = _root;
			while (tmp && tmp->left)
				tmp = tmp->left;
			_start = tmp;
			if (!_end)
				_end = create_node(value_type(), BLACK);
			tmp = _root;
			while (tmp->right && tmp->right->color != D_BLACK)
				tmp = tmp->right;
			tmp->right = _end;
			_end->parent = tmp;
		};

		node_pointer insert(node_pointer node)
		{
			_root = insert(_root, node);
			fix_insert(node);
			fixEndStart();
			return (node);
		};

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
		};

		node_pointer search(const Value &value) const
		{
			return (search(_root, value));
		};

		const_iterator find(const value_type &value) const
		{
			return (const_iterator(search(value)));
		};

		iterator find(const value_type &value)
		{
			node_pointer node = search(value);
			if (node)
				return (iterator(node));
			return (end());
		};

		ft::pair<iterator, bool> insert(const value_type &value)
		{
			node_pointer node = search(value);
			if (node)
				return (ft::pair<iterator, bool>(iterator(node), false));
			node = create_node(value, RED);
			node->right = node->left = NULL;
			insert(node);
			_size++;
			ft::pair<iterator, bool> ret(iterator(node), true);
			return (ret);
		};

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
		};

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
		};

		void swap(red_black_tree &x)
		{
			std::swap(_root, x._root);
			std::swap(_size, x._size);
			std::swap(_start, x._start);
			std::swap(_end, x._end);
			std::swap(_comp, x._comp);
			std::swap(_node_allocator, x._node_allocator);
		};

		node_pointer *get_parent_ptr(node_pointer node)
		{
			if (!node->parent)
				return (&_root);
			else if (node->isLeft())
				return (&node->parent->left);
			else if (node->isRight())
				return (&node->parent->right);
			throw std::exception();
		};

		void swap(node_pointer x, node_pointer y)
		{
			*get_parent_ptr(x) = y;
			*get_parent_ptr(y) = x;
			std::swap(x->parent, y->parent);
			std::swap(x->left, y->left);
			std::swap(x->right, y->right);
			std::swap(x->color, y->color);
			if (x->left)
				x->left->parent = x;
			if (x->right)
				x->right->parent = x;
			if (y->left)
				y->left->parent = y;
			if (y->right)
				y->right->parent = y;
		};

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
		};

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
		};

		/**
		 * @brief Fix insert
		 * @see https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
		 * @param node
		 */
		void fix_insert(node_pointer node) // here we fix the tree after insertion.
		{
			while (node->parent && node->parent->color == RED)
			{
				/* we have a violation */
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
			if (_root)
				_root->color = BLACK;
		};

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
		};

		void print_tree(void) const
		{
			print_tree(_root, 0);
			std::cout << ".----------------------------------." << std::endl;
		};

	  public:
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type)
		{
			for (; first != last; first++)
				insert(*first);
		};
	};
}; // namespace ft
#endif
