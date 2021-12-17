/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:24:51 by aborboll          #+#    #+#             */
/*   Updated: 2021/12/16 23:47:54 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/type_traits.hpp"
#include "Tester.hpp"

template<class T>
struct is_integral
{
	template<class Q = T>
	typename ft::enable_if<ft::is_integral<Q>::value, bool>::type check()
	{
		return true;
	}

	template<class Q = T>
	typename ft::enable_if<!ft::is_integral<Q>::value, bool>::type check()
	{
		return false;
	}
};


class type_traits_tester : public Tester
{
	protected:
		bool	_status;
	public:
		type_traits_tester(void) : Tester("type_traits"), _status(true) {};
		void	setStatus(bool status) { _status = status; }
		bool	getStatus(void) { return (_status); }

		bool	test()
		{
			this->section("is_integral");
			this->expect("int", ft::is_integral<int>::value, std::is_integral<int>::value);
			this->expect("bool", ft::is_integral<bool>::value, std::is_integral<bool>::value);
			this->expect("char", ft::is_integral<char>::value, std::is_integral<char>::value);
			this->expect("wchar_t", ft::is_integral<wchar_t>::value, std::is_integral<wchar_t>::value);
			this->expect("short", ft::is_integral<short>::value, std::is_integral<short>::value);
			this->expect("long", ft::is_integral<long>::value, std::is_integral<long>::value);
			this->expect("long long", ft::is_integral<long long>::value, std::is_integral<long long>::value);
			this->expect("unsigned char", ft::is_integral<unsigned char>::value, std::is_integral<unsigned char>::value);
			this->expect("unsigned short", ft::is_integral<unsigned short>::value, std::is_integral<unsigned short>::value);
			this->expect("unsigned int", ft::is_integral<unsigned int>::value, std::is_integral<unsigned int>::value);
			this->expect("unsigned long", ft::is_integral<unsigned long>::value, std::is_integral<unsigned long>::value);
			this->expect("std::string", ft::is_integral<std::string>::value, std::is_integral<std::string>::value);
			this->expect("float", ft::is_integral<float>::value, std::is_integral<float>::value);
			this->expect("double", ft::is_integral<double>::value, std::is_integral<double>::value);
			this->endSection();
			this->section("enable_if");
			is_integral<float> floatNumber;
			is_integral<int> intNumber;
			this->expect("enable_if", !floatNumber.check() && intNumber.check(), true);
			this->endSection();
			return (_status);
		}
};
