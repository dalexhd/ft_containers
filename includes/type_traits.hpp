/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:47:14 by aborboll          #+#    #+#             */
/*   Updated: 2022/01/14 19:16:07 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace	ft
{
	/**
	 * fn:	enable_if
	 * url: https://en.cppreference.com/w/cpp/types/enable_if
	 *
	 * @brief If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.
	 * This metafunction is a convenient way to leverage SFINAE to conditionally remove functions from overload resolution based on type traits and to provide separate function overloads and specializations for different type traits. std::enable_if can be used as an additional function argument (not applicable to operator overloads), as a return type (not applicable to constructors and destructors), or as a class template or function template parameter.
	 * The behavior of a program that adds specializations for enable_if is undefined.
	*/
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	/**
	 * fn:	is_integral
	 * url: https://en.cppreference.com/w/cpp/types/is_integral
	 *
	 * @brief Checks whether T is an integral type. Provides the member constant value which is equal to true, if T is the type bool, char, char8_t (since C++20), char16_t, char32_t, wchar_t, short, int, long, long long, or any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants. Otherwise, value is equal to false.
	 * The behavior of a program that adds specializations for is_integral or is_integral_v (since C++17) is undefined.
	*/
	template<class T>
	struct is_integral : public std::false_type {};

	template<>
	struct is_integral<int> : public std::true_type {};

	template<>
	struct is_integral<bool> : public std::true_type {};

	template<>
	struct is_integral<char> : public std::true_type {};

	template<>
	struct is_integral<wchar_t> : public std::true_type {};

	template<>
	struct is_integral<short> : public std::true_type {};

	template<>
	struct is_integral<long> : public std::true_type {};

	template<>
	struct is_integral<long long> : public std::true_type {};

	template<>
	struct is_integral<unsigned char> : public std::true_type {};

	template<>
	struct is_integral<unsigned short> : public std::true_type {};

	template<>
	struct is_integral<unsigned int> : public std::true_type {};

	template<>
	struct is_integral<unsigned long> : public std::true_type {};
}

#endif
