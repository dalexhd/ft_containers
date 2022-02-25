/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 00:04:49 by aborboll          #+#    #+#             */
/*   Updated: 2022/02/25 15:11:00 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <functional>

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
}; // namespace ft

#endif
