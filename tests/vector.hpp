/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:28:42 by aborboll          #+#    #+#             */
/*   Updated: 2022/01/20 20:54:32 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.hpp"
#include "Tester.hpp"
#include <vector>

class vector_tester : public Tester
{
	private:
		bool	_status;
	public:
		vector_tester(void) : Tester("vector"), _status(true) {};
		void	setStatus(bool status) { _status = status; }
		bool	getStatus(void) { return (_status); }
		bool	test()
		{
/* 			vector::assign
			vector::at
			vector::back
			vector::begin
			vector::capacity
			vector::clear
			vector::empty
			vector::end
			vector::erase
			vector::front
			vector::get_allocator
			vector::insert
			vector::max_size
			vector::operator=
			vector::operator[]
			vector::pop_back
			vector::push_back
			vector::rbegin
			vector::rend
			vector::reserve
			vector::resize
			vector::size
			vector::swap
			relational operators (vector)
			swap (vector) */
			return (false);
		}
};
