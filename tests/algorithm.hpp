/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:15:36 by aborboll          #+#    #+#             */
/*   Updated: 2022/02/15 13:37:52 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/algorithm.hpp"
#include "Tester.hpp"

// a case-insensitive comparison function:
static bool mycomp(char c1, char c2)
{
	return std::tolower(c1) < std::tolower(c2);
}

class algorithm_tester : public Tester
{
  private:
	bool _status;

  public:
	algorithm_tester(void) : Tester("algorithm"), _status(true){};
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
		this->section("lexicographical_compare");
		char foo[] = "Apple";
		char bar[] = "apartment";
		this->expect(
		    "Using default comparison (operator<)",
		    [&] {
			    return ft::lexicographical_compare(foo, foo + 5, bar, bar + 9);
		    },
		    [&] {
			    return std::lexicographical_compare(foo, foo + 5, bar, bar + 9);
		    });
		this->expect(
		    "Using mycomp as comparison object",
		    [&] {
			    return ft::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp);
		    },
		    [&] {
			    return std::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp);
		    });
		this->expect(
		    "Using default comparison (operator<)",
		    [&] {
			    return ft::lexicographical_compare(bar, bar + 9, foo, foo + 5);
		    },
		    [&] {
			    return std::lexicographical_compare(bar, bar + 9, foo, foo + 5);
		    });
		this->expect(
		    "Using mycomp as comparison object",
		    [&] {
			    return ft::lexicographical_compare(bar, bar + 9, foo, foo + 5, mycomp);
		    },
		    [&] {
			    return std::lexicographical_compare(bar, bar + 9, foo, foo + 5, mycomp);
		    });
		this->endSection();
		return (_status);
	}
};
