/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:24:51 by aborboll          #+#    #+#             */
/*   Updated: 2022/03/03 20:10:27 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/type_traits.hpp"
#include "Tester.hpp"

template <class T> struct is_integral
{
	template <class Q = T>
	typename ft::enable_if<ft::is_integral<Q>::value, bool>::type check()
	{
		return true;
	}

	template <class Q = T>
	typename ft::enable_if<!ft::is_integral<Q>::value, bool>::type check()
	{
		return false;
	}
};

template <class T> struct is_integral_std
{
	template <class Q = T>
	typename std::enable_if<ft::is_integral<Q>::value, bool>::type check()
	{
		return true;
	}

	template <class Q = T>
	typename std::enable_if<!ft::is_integral<Q>::value, bool>::type check()
	{
		return false;
	}
};

class type_traits_tester : public Tester
{
  private:
	bool _status;

  public:
	type_traits_tester(void) : Tester("type_traits"), _status(true){};
	void setStatus(bool status)
	{
		_status = status;
	}
	bool getStatus(void)
	{
		return (_status);
	}
	bool test()
	{
		this->section("is_integral");
		this->expect<bool>(
		    "int", [&] { return ft::is_integral<int>::value; },
		    [&] { return std::is_integral<int>::value; });
		this->expect<bool>(
		    "bool", [&] { return ft::is_integral<bool>::value; },
		    [&] { return std::is_integral<bool>::value; });
		this->expect<bool>(
		    "char", [&] { return ft::is_integral<char>::value; },
		    [&] { return std::is_integral<char>::value; });
		this->expect<bool>(
		    "wchar_t", [&] { return ft::is_integral<wchar_t>::value; },
		    [&] { return std::is_integral<wchar_t>::value; });
		this->expect<bool>(
		    "short", [&] { return ft::is_integral<short>::value; },
		    [&] { return std::is_integral<short>::value; });
		this->expect<bool>(
		    "long", [&] { return ft::is_integral<long>::value; },
		    [&] { return std::is_integral<long>::value; });
		this->expect<bool>(
		    "long long", [&] { return ft::is_integral<long long>::value; },
		    [&] { return std::is_integral<long long>::value; });
		this->expect<bool>(
		    "unsigned char",
		    [&] { return ft::is_integral<unsigned char>::value; },
		    [&] { return std::is_integral<unsigned char>::value; });
		this->expect<bool>(
		    "unsigned short",
		    [&] { return ft::is_integral<unsigned short>::value; },
		    [&] { return std::is_integral<unsigned short>::value; });
		this->expect<bool>(
		    "unsigned int", [&] { return ft::is_integral<unsigned int>::value; },
		    [&] { return std::is_integral<unsigned int>::value; });
		this->expect<bool>(
		    "unsigned long",
		    [&] { return ft::is_integral<unsigned long>::value; },
		    [&] { return std::is_integral<unsigned long>::value; });
		this->expect<bool>(
		    "std::string", [&] { return ft::is_integral<std::string>::value; },
		    [&] { return std::is_integral<std::string>::value; });
		this->expect<bool>(
		    "float", [&] { return ft::is_integral<float>::value; },
		    [&] { return std::is_integral<float>::value; });
		this->expect<bool>(
		    "double", [&] { return ft::is_integral<double>::value; },
		    [&] { return std::is_integral<double>::value; });
		this->endSection();
		this->section("enable_if");
		this->expect<bool>(
		    "enable_if",
		    [&] {
			    is_integral<float> floatNumber;
			    is_integral<int>   intNumber;
			    return !floatNumber.check() && intNumber.check();
		    },
		    [&] {
			    is_integral_std<float> floatNumber;
			    is_integral_std<int>   intNumber;
			    return !floatNumber.check() && intNumber.check();
		    });
		this->endSection();
		return (_status);
	}
};
