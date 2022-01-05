/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:22 by aborboll          #+#    #+#             */
/*   Updated: 2022/01/05 17:45:15 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <memory>

namespace ft
{
	/**
	 * @brief The elements are stored contiguously, which means that elements can be accessed not only through iterators, but also using offsets to regular pointers to elements. This means that a pointer to an element of a vector may be passed to any function that expects a pointer to an element of an array.
	 *
	 * @tparam T The type of the elements.
	 * @tparam Allocator 	An allocator that is used to acquire/release memory and to construct/destroy the elements in that memory. The type must meet the requirements of Allocator.
	 */
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef	T													value_type;
			typedef	Allocator											allocator_type;
			typedef	typename	allocator_type::reference				reference;
			typedef	typename	allocator_type::reference				const_reference;
			typedef	typename	allocator_type::pointer					pointer;
			typedef	typename	allocator_type::const_pointer			const_pointer;
			//typedef typename	ft::vector_iterator<const_pointer>		const_iterator;
			//typedef				ft::reverse_iterator<iterator>			reverse_iterator;
			//typedef				ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef	size_t		size_type;
	};
}

#endif
