/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 12:37:03 by aborboll          #+#    #+#             */
/*   Updated: 2021/12/30 12:45:08 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utility.hpp"
#include "Tester.hpp"

class utility_tester : public Tester
{
	private:
		bool	_status;
	public:
		utility_tester(void) : Tester("utility"), _status(true) {};
		void	setStatus(bool status) { _status = status; }
		bool	getStatus(void) { return (_status); }
		bool	test()
		{
			this->section("pair");
			this->expect("pair & make_pair", [&]{
				ft::pair <std::string,double> product1;                     // default constructor
				ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
				ft::pair <std::string,double> product3 (product2);          // copy constructor
				product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)
				product2.first = "shoes"; // the type of first is string
				product2.second = 39.90; // the type of second is double
				return product1.first == "lightbulbs" &&
					product1.second == 0.99 &&
					product2.first == "shoes" &&
					product2.second == 39.90 &&
					product3.first == "tomatoes" &&
					product3.second == 2.30;
			}, [&]{
				std::pair <std::string,double> product1;                     // default constructor
				std::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
				std::pair <std::string,double> product3 (product2);          // copy constructor
				product1 = std::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)
				product2.first = "shoes"; // the type of first is string
				product2.second = 39.90; // the type of second is double
				return product1.first == "lightbulbs" &&
					product1.second == 0.99 &&
					product2.first == "shoes" &&
					product2.second == 39.90 &&
					product3.first == "tomatoes" &&
					product3.second == 2.30;
			});
			this->endSection();
			return (_status);
		}
};
