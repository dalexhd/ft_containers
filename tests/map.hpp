/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:16:04 by aborboll          #+#    #+#             */
/*   Updated: 2022/04/05 15:12:54 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.hpp"
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
		this->section("member functions");
		this->expect<size_t>(
		    "map::insert(pair)",
		    [&] {
			    ft::map<char, int> mymap;
			    mymap.insert(ft::pair<char, int>('a', 100));
			    mymap.insert(ft::pair<char, int>('z', 200));
			    return (mymap.size());
		    },
		    [&] {
			    std::map<char, int> mymap;
			    mymap.insert(std::pair<char, int>('a', 100));
			    mymap.insert(std::pair<char, int>('z', 200));
			    return (mymap.size());
		    });
		this->expect<int>(
		    "map::insert(iterator)",
		    [&] {
			    ft::map<char, int>                           mymap;
			    ft::pair<ft::map<char, int>::iterator, bool> ret;
			    ret = mymap.insert(ft::pair<char, int>('z', 500));
			    return (ret.second);
		    },
		    [&] {
			    std::map<char, int>                            mymap;
			    std::pair<std::map<char, int>::iterator, bool> ret;
			    ret = mymap.insert(std::pair<char, int>('z', 500));
			    return (ret.second);
		    });
		this->expect<int>(
		    "map::insert(InputIterator)",
		    [&] {
			    ft::map<char, int> mymap;
			    mymap.insert(ft::pair<char, int>('a', 100));
			    mymap.insert(ft::pair<char, int>('z', 200));
			    return (mymap.find('a')->second);
		    },
		    [&] {
			    std::map<char, int> mymap;
			    mymap.insert(std::pair<char, int>('a', 100));
			    mymap.insert(std::pair<char, int>('z', 200));
			    return (mymap.find('a')->second);
		    });
		this->expect<size_t>(
		    "map::size",
		    [&] {
			    ft::map<char, int> mymap;
			    mymap.insert(ft::pair<char, int>('g', 7));
			    mymap.insert(ft::pair<char, int>('f', 6));
			    mymap.insert(ft::pair<char, int>('e', 5));
			    mymap.insert(ft::pair<char, int>('d', 4));
			    mymap.insert(ft::pair<char, int>('c', 3));
			    mymap.insert(ft::pair<char, int>('b', 2));
			    mymap.insert(ft::pair<char, int>('a', 1));
			    mymap.insert(ft::pair<char, int>('h', 8));
			    mymap.insert(ft::pair<char, int>('l', 12));
			    mymap.insert(ft::pair<char, int>('m', 11));
			    return (mymap.size());
		    },
		    [&] {
			    std::map<char, int> mymap;
			    mymap.insert(std::pair<char, int>('g', 7));
			    mymap.insert(std::pair<char, int>('f', 6));
			    mymap.insert(std::pair<char, int>('e', 5));
			    mymap.insert(std::pair<char, int>('d', 4));
			    mymap.insert(std::pair<char, int>('c', 3));
			    mymap.insert(std::pair<char, int>('b', 2));
			    mymap.insert(std::pair<char, int>('a', 1));
			    mymap.insert(std::pair<char, int>('h', 8));
			    mymap.insert(std::pair<char, int>('l', 12));
			    mymap.insert(std::pair<char, int>('m', 11));
			    return (mymap.size());
		    });
		this->expect<size_t>(
		    "map::max_size",
		    [&] {
			    ft::map<int, int> mymap;
			    mymap.insert(ft::pair<char, int>('a', 100));
			    mymap.insert(ft::pair<char, int>('z', 200));
			    mymap.insert(ft::pair<char, int>('b', 400));
			    return (mymap.max_size() + mymap.get_allocator().max_size());
		    },
		    [&] {
			    std::map<char, int> mymap;
			    mymap.insert(std::pair<char, int>('a', 100));
			    mymap.insert(std::pair<char, int>('z', 200));
			    mymap.insert(std::pair<char, int>('b', 400));
			    return (mymap.max_size() + mymap.get_allocator().max_size());
		    });
		this->endSection();
		return (_status);
	}
};
