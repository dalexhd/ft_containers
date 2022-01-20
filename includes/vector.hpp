/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:22 by aborboll          #+#    #+#             */
/*   Updated: 2022/01/20 20:36:43 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <memory>
#include <exception>
#include "iterator.hpp"

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
			size_type _size;
			size_type _capacity;
			allocator_type _allocator;
			pointer _data;

		public:
			explicit vector (const allocator_type& alloc = allocator_type()) : _data(nullptr), _size(0), _capacity(0), _allocator(alloc) {};
			explicit vector (size_type n, const allocator_type & alloc = allocator_type()) : _data(nullptr), _size(0), _capacity(0), _allocator(alloc)
			{
				try
				{
					_data = _allocator.allocacte(n);
					_capacity = 0;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}
			};

			iterator begin()
			{
				return (iterator(_data));
			}

			iterator end()
			{
				return (iterator(_data + _size));
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
				(void)n;
				(void)val;
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
				return *(_data[_size - 1]);
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
				return *(_data[_size - 1]);
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
				return *(_data[0]);
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
				return *(_data[0]);
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

	};
}

#endif
