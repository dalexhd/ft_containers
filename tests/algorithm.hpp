/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:15:36 by aborboll          #+#    #+#             */
/*   Updated: 2021/12/19 14:25:03 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/algorithm.hpp"
#include "Tester.hpp"

// a case-insensitive comparison function:
static  bool mycomp (char c1, char c2)
{
    return std::tolower(c1) < std::tolower(c2);
}

class algorithm_tester : public Tester
{
	private:
		bool	_status;
	public:
		algorithm_tester(void) : Tester("algorithm"), _status(true) {};
		void	setStatus(bool status) { _status = status; }
		bool	getStatus(void) { return (_status); }
		bool	test()
		{
			this->section("lexicographical_compare");
			char foo[] = "Apple";
			char bar[] = "apartment";
			this->expect("Using default comparison (operator<)", ft::lexicographical_compare(foo, foo + 5, bar, bar + 9), true);
			this->expect("Using mycomp as comparison object", ft::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp), false);
			this->endSection();
			return (_status);
		}
};
