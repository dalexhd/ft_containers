/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:09 by aborboll          #+#    #+#             */
/*   Updated: 2022/05/06 14:32:51 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

#include "tree.hpp"

namespace ft
{
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
			val_compare(Compare comp) : _comp(comp){};

			bool operator()(const value_type &lhs, const value_type &rhs) const
			{
				return (_comp(lhs.first, rhs.first));
			};
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
		typedef node<value_type>                         _node;
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
		map(const map &other)
		    : _tree(other._tree), _allocator(other._allocator), _comp(other._comp){};
		// Destructor
		~map()
		{
			_tree.clear();
		};

	  public:
		/**
		 * @brief Returns an iterator referring to the first element in the map container.
		 * Because map containers keep their elements ordered at all times, begin points to the element that goes first following the container's sorting criterion.
		 * If the container is empty, the returned iterator value shall not be dereferenced.
		 *
		 * @return iterator An iterator to the first element in the container.
		 */
		iterator begin()
		{
			return (_tree.begin());
		};

		/**
		 * @brief Returns an iterator referring to the first element in the map container.
		 * Because map containers keep their elements ordered at all times, begin points to the element that goes first following the container's sorting criterion.
		 * If the container is empty, the returned iterator value shall not be dereferenced.
		 *
		 * @return const_iterator A const iterator to the first element in the container.
		 */
		const_iterator begin() const
		{
			return (_tree.begin());
		};

		/**
		 * @brief Returns an iterator referring to the past-the-end element in the map container.
		 * The past-the-end element is the theoretical element that would follow the last element in the map container. It does not point to any element, and thus shall not be dereferenced.
		 * Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, this function is often used in combination with map::begin to specify a range including all the elements in the container.
		 * If the container is empty, this function returns the same as map::begin.
		 *
		 * @return iterator An iterator to the past-the-end element in the container.
		 */
		iterator end()
		{
			return (_tree.end());
		};

		/**
		 * @brief Returns an iterator referring to the past-the-end element in the map container.
		 * The past-the-end element is the theoretical element that would follow the last element in the map container. It does not point to any element, and thus shall not be dereferenced.
		 * Because the ranges used by functions of the standard library do not include the element pointed by their closing iterator, this function is often used in combination with map::begin to specify a range including all the elements in the container.
		 * If the container is empty, this function returns the same as map::begin.
		 *
		 * @return const_iterator A const iterator to the past-the-end element in the container.
		 */
		const_iterator end() const
		{
			return (const_iterator(_tree.end()));
		};

		/**
		 * @brief Return reverse iterator to reverse beginning
		 * Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
		 * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
		 * rbegin points to the element preceding the one that would be pointed to by member end.
		 *
		 * @return reverse_iterator A reverse iterator to the reverse beginning of the sequence container.
		 */
		reverse_iterator rbegin()
		{
			return (_tree.rbegin());
		};

		/**
		 * @brief Return reverse iterator to reverse beginning
		 * Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
		 * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
		 * rbegin points to the element preceding the one that would be pointed to by member end.
		 *
		 * @return const_reverse_iterator A const reverse iterator to the reverse beginning of the sequence container.
		 */
		const_reverse_iterator rbegin() const
		{
			return (_tree.rbegin());
		};

		/**
		 * @brief Returns a reverse iterator pointing to the theoretical element right before the first element in the map container (which is considered its reverse end).
		 * The range between map::rbegin and map::rend contains all the elements of the container (in reverse order).
		 *
		 * @return reverse_iterator A reverse iterator to the reverse end of the sequence container.
		 */
		reverse_iterator rend()
		{
			return (_tree.rend());
		};

		/**
		 * @brief Returns a reverse iterator pointing to the theoretical element right before the first element in the map container (which is considered its reverse end).
		 * The range between map::rbegin and map::rend contains all the elements of the container (in reverse order).
		 *
		 * @return const_reverse_iterator A const reverse iterator to the reverse end of the sequence container.
		 */
		const_reverse_iterator rend() const
		{
			return (_tree.rend());
		};

		/**
		 * @brief Returns an iterator pointing to the first element in the container whose key is not considered to go before k (i.e., either it is equivalent or goes after).
		 * The function uses its internal comparison object (key_comp) to determine this, returning an iterator to the first element for which key_comp(element_key,k) would return false.
		 * If the map class is instantiated with the default comparison type (less), the function returns an iterator to the first element whose key is not less than k.
		 * A similar member function, upper_bound, has the same behavior as lower_bound, except in the case that the map contains an element with a key equivalent to k: In this case, lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.
		 *
		 * @param k Key to search for.
		 * Member type key_type is the type of the elements in the container, defined in map as an alias of its first template parameter (Key).
		 * @return iterator A iterator to the the first element in the container whose key is not considered to go before k, or map::end if all keys are considered to go before k.
		 */
		iterator lower_bound(const key_type &k)
		{
			iterator it = begin();
			while (it != end())
			{
				if (!_comp(it->first, k))
					return (it);
				it++;
			}
			return begin();
		};

		/**
		 * @brief Returns an iterator pointing to the first element in the container whose key is not considered to go before k (i.e., either it is equivalent or goes after).
		 * The function uses its internal comparison object (key_comp) to determine this, returning an iterator to the first element for which key_comp(element_key,k) would return false.
		 * If the map class is instantiated with the default comparison type (less), the function returns an iterator to the first element whose key is not less than k.
		 * A similar member function, upper_bound, has the same behavior as lower_bound, except in the case that the map contains an element with a key equivalent to k: In this case, lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.
		 *
		 * @param k Key to search for.
		 * Member type key_type is the type of the elements in the container, defined in map as an alias of its first template parameter (Key).
		 * @return iterator A const iterator to the the first element in the container whose key is not considered to go before k, or map::end if all keys are considered to go before k.
		 */
		const_iterator lower_bound(const key_type &k) const
		{
			const_iterator it = begin();
			while (it != end())
			{
				if (!_comp(it->first, k))
					return (it);
				it++;
			}
			return end();
		};

		/**
		 * @brief Returns an iterator pointing to the first element in the container whose key is considered to go after k.
		 * The function uses its internal comparison object (key_comp) to determine this, returning an iterator to the first element for which key_comp(k,element_key) would return true.
		 * If the map class is instantiated with the default comparison type (less), the function returns an iterator to the first element whose key is greater than k.
		 * A similar member function, lower_bound, has the same behavior as upper_bound, except in the case that the map contains an element with a key equivalent to k: In this case lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.
		 *
		 * @param k Key to search for.
		 * @return iterator A iterator to the the first element in the container whose key is considered to go after k, or map::end if all keys are considered to go before k.
		 */
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
		};

		/**
		 * @brief Returns an iterator pointing to the first element in the container whose key is considered to go after k.
		 * The function uses its internal comparison object (key_comp) to determine this, returning an iterator to the first element for which key_comp(k,element_key) would return true.
		 * If the map class is instantiated with the default comparison type (less), the function returns an iterator to the first element whose key is greater than k.
		 * A similar member function, lower_bound, has the same behavior as upper_bound, except in the case that the map contains an element with a key equivalent to k: In this case lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.
		 *
		 * @param k Key to search for.
		 * @return const_iterator A const iterator to the the first element in the container whose key is considered to go after k, or map::end if all keys are considered to go before k.
		 */
		const_iterator upper_bound(const key_type &k) const
		{
			const_iterator it = begin();
			while (it != end())
			{
				if (_comp(k, it->first))
					return (it);
				it++;
			}
			return end();
		};

	  public:
		/**
		 * @brief Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
		 *
		 */
		void clear()
		{
			_tree.clear();
		};

		/**
		 * @brief Searches the container for elements with a key equivalent to k and returns the number of matches.
		 * Because all elements in a map container are unique, the function can only return 1 (if the element is found) or zero (otherwise).
		 * Two keys are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).
		 *
		 * @param k  Key to search for.
		 * @return size_type The number of elements with a key equivalent to k.
		 */
		size_type count(const key_type &k) const
		{
			size_type      n = 0;
			const_iterator it = begin();
			while (it != end())
			{
				if (!_comp(it->first, k) && !_comp(k, it->first))
					n++;
				it++;
			}
			return (n);
		};

		/**
		 * @brief Returns whether the map container is empty (i.e. whether its size is 0).
		 * This function does not modify the container in any way. To clear the content of a map container, see map::clear.
		 *
		 * @return bool if the map container is empty, false otherwise.
		 */
		bool empty() const
		{
			return (_tree.size() == 0);
		};

		/**
		 * @brief Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
		 * Because the elements in a map container have unique keys, the range returned will contain a single element at most.
		 * If no matches are found, the range returned has a length of zero, with both iterators pointing to the first element that has a key considered to go after k according to the container's internal comparison object (key_comp).
		 * Two keys are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).
		 *
		 * @param k Key to search for.
		 * @return ft::pair<const_iterator, const_iterator> The function returns a pair, whose member pair::first is the lower bound of the range (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
		 */
		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		};

		/**
		 * @brief Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
		 * Because the elements in a map container have unique keys, the range returned will contain a single element at most.
		 * If no matches are found, the range returned has a length of zero, with both iterators pointing to the first element that has a key considered to go after k according to the container's internal comparison object (key_comp).
		 * Two keys are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).
		 *
		 * @param k Key to search for.
		 * @return ft::pair<const_iterator, const_iterator> The function returns a const pair, whose member pair::first is the lower bound of the range (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
		 */
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		};

		void erase(iterator position)
		{
			_node *ptr = position.getPtr();
			erase(ptr->data.first);
		};

		/**
		 * @brief Removes from the container all elements whose key is equivalent to k.
		 *
		 * @param k Key of the element to be removed from the map.
		 * @return size_type The number of elements removed.
		 */
		size_type erase(const key_type &k)
		{
			ft::node<value_type> *ptr = _tree.search(value_type(k, mapped_type()));
			if (ptr == NULL)
				return (0);
			_tree.delete_node(ptr);
			return (1);
		};

		/**
		 * @brief Removes from the container a range of elements.
		 *
		 * @param first Iterator to the first element to remove.
		 * @param last Iterator to the last element to remove.
		 */
		void erase(iterator first, iterator last)
		{
			for (; first != last; first++)
				erase(first);
		};

		/**
		 * @brief Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
		 *
		 * @param k Key to search for.
		 * @return iterator An iterator to the element with a key equivalent to k, or map::end if such an element is not found.
		 */
		iterator find(const key_type &k)
		{
			return (iterator(_tree.find(value_type(k, mapped_type()))));
		};

		/**
		 * @brief Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
		 *
		 * @param k Key to search for.
		 * @return const_iterator A const iterator to the element with a key equivalent to k, or map::end if such an element is not found.
		 */
		const_iterator find(const key_type &k) const
		{
			return (const_iterator(_tree.find(value_type(k, mapped_type()))));
		};

		/**
		 * @brief Returns a copy of the allocator object associated with the map.
		 *
		 * @return allocator_type The allocator object associated with the map.
		 */
		allocator_type get_allocator() const
		{
			return (_tree.get_allocator());
		};

		/**
		 * @brief Inserts a new element into the map container with the specified key and value.
		 *
		 * @param value Value to be copied to (or moved as) the inserted element.
		 * @return ft::pair<iterator, bool> The single element versions (1) return a pair,
		 * with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map.
		 * The pair::second element in the pair is set to true if a new element was inserted or false if an equivalent key already existed.
		 */
		ft::pair<iterator, bool> insert(const value_type &value)
		{
			ft::pair<typename rb_tree::iterator, bool> res = _tree.insert(value);
			return (ft::pair<iterator, bool>(iterator(res.first), res.second));
		};

		/**
		 * @brief Inserts a new element into a specified position in the map container with the specified key and value.
		 *
		 * @param position Iterator to the position in the map where the new element is inserted.
		 * @param val Value to be copied to (or moved as) the inserted element.
		 * @return iterator An iterator pointing to the newly inserted element.
		 */
		iterator insert(iterator position, const value_type &val)
		{
			(void) position;
			return (insert(val).first);
		};

		/**
		 * @brief Inserts a number of elements into the map container from another input iterator.
		 *
		 * @tparam InputIterator An input iterator type that points to elements to be inserted.
		 * @param first Iterator to the first element to insert.
		 * @param last Iterator to the last element to insert.
		 */
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL)
		{
			for (; first != last; first++)
				insert(*first);
		};

		/**
		 * @brief Returns a copy of the comparison object used by the container to compare keys.
		 *
		 * @return key_compare The comparison object.
		 */
		key_compare key_comp() const
		{
			return (_comp);
		};

		/**
		 * @brief  Returns the maximum number of elements that the map container can hold.
		 * This is the maximum potential size the container can reach due to known system or library implementation limitations, but the container is by no means guaranteed to be able to reach that size: it can still fail to allocate storage at any point before that size is reached.
		 *
		 * @return size_type The maximum number of elements that the map container can hold.
		 */
		size_type max_size() const
		{
			return (_tree.max_size());
		};

		/**
		 * @brief Returns the number of elements in the map container.
		 *
		 * @return size_type The number of elements in the map container.
		 */
		size_type size() const
		{
			return (_tree.size());
		};

		/**
		 * @brief Exchanges the content of the container by the content of x, which is another map of the same type. Sizes may differ.
		 *
		 * @param x Another map container of the same type as this (i.e., with the same template parameters, Key, T, Compare and Alloc) whose content is swapped with that of this container.
		 */
		void swap(map &x)
		{
			_tree.swap(x._tree);
		};

		/**
		 * @brief Returns a comparison object that can be used to compare two elements to get whether the key of the first one goes before the second.
		 *
		 * @return value_compare The comparison object for element values.
		 */
		value_compare value_comp() const
		{
			return (_tree.value_comp());
		};

	  public:
		/**
		 * @brief  Assigns new contents to the container, replacing its current content.
		 * Copies all the elements from x into the container, changing its size accordingly.
		 * The container preserves its current allocator, which is used to allocate additional storage if needed.
		 *
		 * @param x A map object of the same type (i.e., with the same template parameters, key, T, Compare and Alloc).
		 * @return map const&
		 */
		map const &operator=(map &x)
		{
			if (this == &x)
				return (*this);
			_tree.reset();
			std::swap(_allocator, x._allocator);
			std::swap(_comp, x._comp);
			for (const_iterator it = x.begin(); it != x.end(); it++)
				this->insert(*it);
			return (*this);
		};

		/**
		 * @brief If k matches the key of an element in the container, the function returns a reference to its mapped value.
		 * If k does not match the key of any element in the container, the function inserts a new element with that key and returns a reference to its mapped value.
		 * Notice that this always increases the container size by one, even if no mapped value is assigned to the element (the element is constructed using its default constructor).
		 * A similar member function, map::at, has the same behavior when an element with the key exists, but throws an exception when it does not.
		 *
		 * @param k Key value of the element whose mapped value is accessed.
		 * @return mapped_type& A reference to the mapped value of the element with a key value equivalent to k.
		 */
		mapped_type &operator[](const key_type &k)
		{
			if (_tree.find(value_type(k, mapped_type())) == _tree.end())
				return (insert(value_type(k, mapped_type())).first->second);
			return _tree.find(value_type(k, mapped_type()))->second;
		};

	  public:
		void print(void)
		{
			_tree.print_tree();
		};
	};

	template <class Key, class Value, class Compare, class Alloc>
	bool operator==(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename map<Key, Value, Compare, Alloc>::const_iterator it = lhs.begin();
		while (it != lhs.end())
		{
			if (rhs.find(it->first) == rhs.end())
				return (false);
			it++;
		}
		return (true);
	};

	template <class Key, class Value, class Compare, class Alloc>
	bool operator!=(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	};

	template <class Key, class Value, class Compare, class Alloc>
	bool operator<(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <class Key, class Value, class Compare, class Alloc>
	bool operator<=(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		return (!operator<(rhs, lhs));
	};

	template <class Key, class Value, class Compare, class Alloc>
	bool operator>(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		return (operator<(rhs, lhs));
	};

	template <class Key, class Value, class Compare, class Alloc>
	bool operator>=(const map<Key, Value, Compare, Alloc> &lhs, const map<Key, Value, Compare, Alloc> &rhs)
	{
		return (!operator<(lhs, rhs));
	};

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	};
}; // namespace ft

#endif
