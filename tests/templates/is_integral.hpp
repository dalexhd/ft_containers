/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:24:51 by aborboll          #+#    #+#             */
/*   Updated: 2021/12/16 20:06:46 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Tester.hpp"
#include "../../includes/templates/is_integral.hpp"

class is_integral_tester : public Tester
{
	protected:
		bool	_status;
	public:
		is_integral_tester(void) : Tester("is_integral"), _status(true) {};
		void	setStatus(bool status) { _status = status; }
		bool	getStatus(void) { return (_status); }
		bool	test()
		{
			this->expect("int", ft::is_integral<int>::value, true);
			this->expect("bool", ft::is_integral<bool>::value, true);
			this->expect("char", ft::is_integral<char>::value, true);
			this->expect("wchar_t", ft::is_integral<wchar_t>::value, true);
			this->expect("short", ft::is_integral<short>::value, true);
			this->expect("long", ft::is_integral<long>::value, true);
			this->expect("long long", ft::is_integral<long long>::value, true);
			this->expect("unsigned char", ft::is_integral<unsigned char>::value, true);
			this->expect("unsigned short", ft::is_integral<unsigned short>::value, true);
			this->expect("unsigned int", ft::is_integral<unsigned int>::value, true);
			this->expect("unsigned long", ft::is_integral<unsigned long>::value, true);
			this->expect("std::string", ft::is_integral<std::string>::value, false);
			this->expect("float", ft::is_integral<float>::value, false);
			this->expect("double", ft::is_integral<double>::value, false);
			return (_status);
		}
};
