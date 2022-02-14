/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:22 by aborboll          #+#    #+#             */
/*   Updated: 2022/02/14 18:59:57 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <memory>
#include <exception>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"

namespace ft
{
	/**
	 * @brief The elements are stored contiguously, which means that elements can be accessed not only through iterators, but also using offsets to regular pointers to elements. This means that a pointer to an element of a vector may be passed to any function that expects a pointer to an element of an array.
	 *
	 * @tparam T The type of the elements.
	 * @tparam Allocator 	An allocator that is used to acquire/release memory and to construct/destroy the elements in that memory. The type must meet the requirements of Allocator.
	 */
	template<typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef	T															value_type;
			typedef	Allocator													allocator_type;
			typedef	typename	allocator_type::reference						reference;
			typedef	typename	allocator_type::reference						const_reference;
			typedef	typename	allocator_type::pointer							pointer;
			typedef	typename	allocator_type::const_pointer					const_pointer;
			typedef typename	ft::iterator<pointer>							iterator;
			typedef typename	ft::iterator<const_pointer>						const_iterator;
			typedef				ft::reverse_iterator<iterator>					reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef	size_t		size_type;
		private:
			size_type			_size;
			size_type			_capacity;
			allocator_type		_allocator;
			pointer				_data;
			size_type			diff(iterator first, iterator last)
			{
				return (last - first);
			}
		public:
			explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc), _data(_allocator.allocate(0)) {};
			vector (const vector& x) : _size(x._size), _capacity(x._capacity), _allocator(x._allocator), _data(NULL)
			{
				_data = _allocator.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(&_data[i], x._data[i]);
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<	!ft::is_integral<InputIterator>::value>::type* = NULL
			) : _size(0), _capacity(0), _allocator(alloc), _data(_allocator.allocate(0))
			{
				while (first != last)
				{
					push_back(*first);
					first++;
				}
			}
			explicit vector (size_type n,
				const value_type& val = value_type(),
				const allocator_type & alloc = allocator_type()
			) : _size(n), _capacity(n), _allocator(alloc)
			{
				try
				{
					_data = _allocator.allocate(_capacity);
					while (n--)
						_allocator.construct(&_data[n], val);
				}
				catch (std::exception & e)
				{
					std::cerr << e.what() << std::endl;
				}
			};

			/**
			 * @brief This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
			 *
			 */
			~vector()
			{
				clear();
				_allocator.deallocate(_data, _capacity);
			}

			reference operator* () const
			{
				return (*_data);
			}

			reference operator[] (size_type n) {
				return (_data[n]);
			};

			const_reference operator[] (size_type n) const {
					return (_data[n]);
			};

			vector& operator= (const vector& x)
			{
				clear();
				insert(begin(), x.begin(), x.end());
				return (*this);
			}

			iterator begin()
			{
				return (iterator(_data));
			}

			const_iterator begin() const
			{
				return (const_iterator(_data));
			}

			iterator end()
			{
				return (iterator(_data + _size));
			}

			/**
			 * @brief Removes from the vector either a single element (position) or a range of elements ([first,last)).
			 * This effectively reduces the container size by the number of elements removed, which are destroyed.
			 * Because vectors use an array as their underlying storage, erasing elements in positions other than the vector end causes the container to relocate all the elements after the segment erased to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
			 *
			 * @param position Iterator pointing to a single element to be removed from the vector.
			 * Member types iterator and const_iterator are random access iterator types that point to elements.
			 * @return iterator An iterator pointing to the new location of the element that followed the last element erased by the function call. This is the container end if the operation erased the last element in the sequence.
			 * Member type iterator is a random access iterator type that points to elements.
			 */
			iterator erase (iterator position)
			{
				return erase(position, position + 1);
			}

			/**
			 * @brief Removes from the vector either a single element (position) or a range of elements ([first,last)).
			 * This effectively reduces the container size by the number of elements removed, which are destroyed.
			 * Because vectors use an array as their underlying storage, erasing elements in positions other than the vector end causes the container to relocate all the elements after the segment erased to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
			 *
			 * @param position Iterator pointing to a single element to be removed from the vector.
			 * Member types iterator and const_iterator are random access iterator types that point to elements.
			 * @param last Iterators specifying a range within the vector] to be removed: [first,last). i.e., the range includes all the elements between first and last, including the element pointed by first but not the one pointed by last.
			 * Member types iterator and const_iterator are random access iterator types that point to elements.
			 * @return iterator An iterator pointing to the new location of the element that followed the last element erased by the function call. This is the container end if the operation erased the last element in the sequence.
			 * Member type iterator is a random access iterator type that points to elements.
			 */
			iterator erase (iterator first, iterator last)
			{
				iterator		it;
				size_type		i;

				i = diff(first, last);
				for (it = first; it != last; it++)
					_allocator.destroy(&*it);
				for (it = first; it + i != end(); it++)
					*it = *(it + i);
				_size -= i;
				return (first);
			}

			const_iterator end() const
			{
				return (iterator(_data + _size));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			const_iterator cend() const
			{
				return (iterator(_data + _size));
			}

			/**
			 * @brief Resizes the container so that it contains n elements.
			 * If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
			 * If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
			 * If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
			 * Notice that this function changes the actual content of the container by inserting or erasing elements from it.
			 *
			 * @param n New container size, expressed in number of elements. Member type size_type is an unsigned integral type.
			 * @param val Object whose content is copied to the added elements in case that n is greater than the current container size. If not specified, the default constructor is used instead. Member type value_type is the type of the elements in the container, defined in vector as an alias of the first template parameter (T).
			 */
			void resize (size_type n, value_type val = value_type())
			{
				if (n > _capacity)
					reserve(n);
				while (_size < n)
					push_back(val);
				while (_size > n)
					pop_back();
			}

			/**
			 * @brief Returns a reference to the element at position n in the vector.
			 * The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.
			 *
			 * @param n Position of an element in the container.
			 * If this is greater than, or equal to, the vector size, an exception of type out_of_range is thrown.
			 * Notice that the first element has a position of 0 (not 1).
			 * Member type size_type is an unsigned integral type.
			 * @return reference The element at the specified position in the container.
			 * It returns a reference.
			 */
			reference at (size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return (_data[n]);
			}

			/**
			 * @brief Returns a reference to the element at position n in the vector.
			 * The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size). This is in contrast with member operator[], that does not check against bounds.
			 *
			 * @param n Position of an element in the container.
			 * If this is greater than, or equal to, the vector size, an exception of type out_of_range is thrown.
			 * Notice that the first element has a position of 0 (not 1).
			 * Member type size_type is an unsigned integral type.
			 * @return reference The element at the specified position in the container.
			 * It returns a const_reference.
			 */
			const_reference at (size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector");
				return (_data[n]);
			}

			/**
			 * @brief Returns a reference to the last element in the vector.
			 * Unlike member vector::end, which returns an iterator just past this element, this function returns a direct reference.
			 * Calling this function on an empty container causes undefined behavior.
			 *
			 * @return reference A reference to the last element in the vector.
			 */
			reference back()
			{
				return (_data[_size - 1]);
			}

			/**
			 * @brief Returns a const_reference to the last element in the vector.
			 * Unlike member vector::end, which returns an iterator just past this element, this function returns a direct reference.
			 * Calling this function on an empty container causes undefined behavior.
			 *
			 * @return const_reference A reference to the last element in the vector.
			 */
			const_reference back() const
			{
				return (_data[_size - 1]);
			}

			/**
			 * @brief Returns a reference to the first element in the vector.
			 * Unlike member vector::begin, which returns an iterator to this same element, this function returns a direct reference.
			 * Calling this function on an empty container causes undefined behavior.
			 *
			 * @return reference A reference to the first element in the vector container.
			 */
			reference front()
			{
				return (_data[0]);
			}

			/**
			 * @brief Returns a const_reference to the first element in the vector.
			 * Unlike member vector::begin, which returns an iterator to this same element, this function returns a direct reference.
			 * Calling this function on an empty container causes undefined behavior.
			 *
			 * @return const_reference A const_reference to the first element in the vector container.
			 */
			const_reference front() const
			{
				return (_data[0]);
			}

			/**
			 * @brief Returns the maximum number of elements that the vector can hold.
			 * This is the maximum potential size the container can reach due to known system or library implementation limitations, but the container is by no means guaranteed to be able to reach that size: it can still fail to allocate storage at any point before that size is reached.
			 *
			 * @return size_type The maximum number of elements a vector container can hold as content.
			 */
			size_type max_size() const
			{
				return (_allocator.max_size());
			}

			/**
			 * @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
			 * This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
			 * Notice that this capacity does not suppose a limit on the size of the vector. When this capacity is exhausted and more is needed, it is automatically expanded by the container (reallocating it storage space). The theoretical limit on the size of a vector is given by member max_size.
			 * The capacity of a vector can be explicitly altered by calling member vector::reserve.
			 *
			 * @return size_type The size of the currently allocated storage capacity in the vector, measured in terms of the number elements it can hold.
			 */
			size_type capacity() const
			{
				return (_capacity);
			}

			/**
			 * @brief Returns the number of elements in the vector.
			 * This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
			 *
			 * @return size_type The number of elements in the container.
			 */
			size_type size() const
			{
				return (_size);
			}

			/**
			 * @brief Returns whether the vector is empty (i.e. whether its size is 0).
			 * This function does not modify the container in any way. To clear the content of a vector, see vector::clear.
			 *
			 * @return true if the container size is 0, false otherwise.
			 */
			bool empty() const
			{
				return (_size == 0);
			}

			/**
			 * @brief Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
			 *
			 */
			void clear()
			{
				while (_size)
					pop_back();
			}

			/**
			 * @brief Requests that the vector capacity be at least enough to contain n elements.
			 * If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
			 * In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
			 * This function has no effect on the vector size and cannot alter its elements.
			 *
			 * @param n Minimum capacity for the vector.
			 * Note that the resulting vector capacity may be equal or greater than n.
			 * Member type size_type is an unsigned integral type.
			 */
			void reserve (size_type n)
			{

				if (n > max_size())
					throw std::length_error("Allocation size exceeds maximum supported size");
				else if (n > _capacity)
				{
					T * tmp = _allocator.allocate(n);
					size_type newSize;
					for (newSize = 0; newSize < _size; newSize++)
						_allocator.construct(&tmp[newSize], _data[newSize]);
					clear();
					_allocator.deallocate(_data, _capacity);
					_data = tmp;
					_capacity = n;
					_size = newSize;
				}
			}

			/**
			 * @brief  Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
			 * The new contents are elements constructed from each of the elements in the range between first and last, in the same order.
			 *
			 * @param n New size for the container.
			 * Member type size_type is an unsigned integral type.
			 * @param val Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
			 * Member type value_type is the type of the elements in the container, defined in vector as an alias of its first template parameter (T).
			 */
			void assign (size_type n, const value_type& val)
			{
				reserve(n);
				clear();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				clear();
				insert(begin(), first, last);
			}

			/**
			 * @brief Add element at the end
			 * Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
			 * This effectively increases the container size by one, which causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
			 *
			 * @param val Value to be copied (or moved) to the new element.
			 * Member type value_type is the type of the elements in the container, defined in vector as an alias of its first template parameter (T).
			 */
			void push_back (const value_type& val)
			{
				if (_size == _capacity)
					reserve((_size + 1) * 2); // See https://stackoverflow.com/q/1100311 in order to understand why it's *2
				_allocator.construct(_data + _size++, val);
			}

			/**
			 * @brief Removes the last element in the vector, effectively reducing the container size by one.
			 */
			void pop_back()
			{
				if (_size > 0)
					_allocator.destroy(&_data[--_size]);
			}

			/**
			 * @brief Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
			 * After the call to this member function, the elements in this container are those which were in x before the call, and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
			 * Notice that a non-member function exists with the same name, swap, overloading that algorithm with an optimization that behaves like this member function.
			 *
			 * @param x Another vector container of the same type (i.e., instantiated with the same template parameters, T and Alloc) whose content is swapped with that of this container.
			 */
			void swap (vector& x)
			{
				std::swap(_data, x._data);
				std::swap(_size, x._size);
				std::swap(_capacity, x._capacity);
				std::swap(_allocator, x._allocator);
			}

			/**
			 * @brief The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
			 This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
			 Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to relocate all the elements that were after position to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
			 The parameters determine how many elements are inserted and to which values they are initialized:
			 *
			 * @param position Position in the vector where the new elements are inserted.
			 iterator is a member type, defined as a random access iterator type that points to elements.
			 * @param val Value to be copied (or moved) to the inserted elements.
			 Member type value_type is the type of the elements in the container, defined in deque as an alias of its first template parameter (T).
			 * @return iterator An iterator that points to the first of the newly inserted elements.
			 Member type iterator is a random access iterator type that points to elements.
			 If reallocations happen, the storage is allocated using the container's allocator, which may throw exceptions on failure (for the default allocator, bad_alloc is thrown if the allocation request does not succeed).
			 */
			iterator insert (iterator position, const value_type& val)
			{
				size_type index = position - begin();
				insert(position, 1, val);
				return begin() + index;
			}

			/**
			 * @brief The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
			 This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
			 Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to relocate all the elements that were after position to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
			 The parameters determine how many elements are inserted and to which values they are initialized:
			 *
			 * @param position Position in the vector where the new elements are inserted.
			 iterator is a member type, defined as a random access iterator type that points to elements.
			 * @param n Number of elements to insert. Each element is initialized to a copy of val.
			 Member type size_type is an unsigned integral type.
			 * @param val Value to be copied (or moved) to the inserted elements.
			 Member type value_type is the type of the elements in the container, defined in deque as an alias of its first template parameter (T).
			 */
			void insert (iterator position, size_type n, const value_type& val)
			{
				vector<T>	first(begin(), position);
				vector<T>	last(position, end());

				for (size_type i = 0; i < n; i++)
					first.push_back(val);
				for (iterator it = last.begin(); it != last.end(); it++)
					first.push_back(*it);
				clear();
				swap(first);
			}

			/**
			 * @brief The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
			 This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
			 Because vectors use an array as their underlying storage, inserting elements in positions other than the vector end causes the container to relocate all the elements that were after position to their new positions. This is generally an inefficient operation compared to the one performed for the same operation by other kinds of sequence containers (such as list or forward_list).
			 The parameters determine how many elements are inserted and to which values they are initialized:
			 *
			 * @tparam InputIterator
			 * @param position Position in the vector where the new elements are inserted.
			 * iterator is a member type, defined as a random access iterator type that points to elements.
			 * @param first Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position (in the same order).
			 * Notice that the range includes all the elements between first and last, including the element pointed by first but not the one pointed by last.
			 * The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.
			 * @param last Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position (in the same order).
			 * Notice that the range includes all the elements between first and last, including the element pointed by first but not the one pointed by last.
			 * The function template argument InputIterator shall be an input iterator type that points to elements of a type from which value_type objects can be constructed.
			 */
 			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				while (first != last)
				{
					position = insert(position, *first) + 1;
					++first;
				}
			}

			/**
			 * @brief Returns a copy of the allocator object associated with the vector.
			 *
			 * @return allocator_type The allocator.
			 * Member type allocator_type is the type of the allocator used by the container, defined in vector as an alias of its second template parameter (Alloc).
			 */
			allocator_type get_allocator() const
			{
				return (_allocator);
			}
	};

	template <class T, class Allocator>
	bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i]) return (false);
		return (true);
	}

	template <class T, class Allocator>
	bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Allocator>
	bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Allocator>
	bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Allocator>
	bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Allocator>
	bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
