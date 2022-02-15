/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:16:04 by aborboll          #+#    #+#             */
/*   Updated: 2022/02/15 18:21:38 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.hpp"
#include "Tester.hpp"
#include <map>

class map_tester : public Tester
{
  private:
	bool _status;

  public:
	map_tester(void) : Tester("map"), _status(true){};
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
		return (_status);
	}
};
