/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:16:04 by aborboll          #+#    #+#             */
/*   Updated: 2022/03/22 18:32:15 by aborboll         ###   ########.fr       */
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
		this->expect<bool>(
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
		/* this->expect(
		    "map::insert(InputIterator)",
		    [&] {
		        ft::map<char, int>           mymap;
		        ft::map<char, int>::iterator it = mymap.begin();
		        mymap.insert(it, ft::pair<char, int>('b', 300)); // max efficiency inserting
		        mymap.insert(it, ft::pair<char, int>('c', 400)); // no max efficiency inserting

		        // third insert function version (range insertion):
		        ft::map<char, int> anothermap;
		        anothermap.insert(mymap.begin(), mymap.find('c'));

		        std::string res = "";
		        for (it = mymap.begin(); it != mymap.end(); ++it)
		            res += std::to_string(it->first) + " " + std::to_string(it->second) + " ";
		        for (it = anothermap.begin(); it != anothermap.end(); ++it)
		            res += std::to_string(it->first) + " " + std::to_string(it->second) + " ";
		        return (res == "b 300 c 400 ");
		    },
		    [&] {
		        std::map<char, int>           mymap;
		        std::map<char, int>::iterator it = mymap.begin();
		        mymap.insert(it, std::pair<char, int>('b', 300)); // max efficiency inserting
		        mymap.insert(it, std::pair<char, int>('c', 400)); // no max efficiency inserting

		        // third insert function version (range insertion):
		        std::map<char, int> anothermap;
		        anothermap.insert(mymap.begin(), mymap.find('c'));
		        std::string res = "";
		        for (it = mymap.begin(); it != mymap.end(); ++it)
		            res += std::to_string(it->first) + " " + std::to_string(it->second) + " ";
		        for (it = anothermap.begin(); it != anothermap.end(); ++it)
		            res += std::to_string(it->first) + " " + std::to_string(it->second) + " ";
		        return (res == "b 300 c 400 ");
		    }); */
		this->expect<size_t>(
		    "map::size",
		    [&] {
			    ft::map<char, int> mymap;
			    mymap.insert(ft::pair<char, int>('a', 5));
			    mymap.insert(ft::pair<char, int>('b', 3));
			    mymap.insert(ft::pair<char, int>('c', 2));
			    mymap.insert(ft::pair<char, int>('d', 4));
			    mymap.insert(ft::pair<char, int>('e', 7));
			    mymap.insert(ft::pair<char, int>('f', 6));
			    mymap.insert(ft::pair<char, int>('g', 8));
				mymap.print();
			    return (mymap.size());
		    },
		    [&] {
			    std::map<char, int> mymap;
			    mymap.insert(std::pair<char, int>('a', 100));
			    mymap.insert(std::pair<char, int>('z', 200));
			    mymap.insert(std::pair<char, int>('b', 400));
			    return (mymap.size());
		    });
		this->expect<size_t>(
		    "map::max_size",
		    [&] {
			    ft::map<int, int> mymap;
			    mymap.insert(ft::pair<int, int>(1, 2));
			    mymap.insert(ft::pair<int, int>(2, 3));
			    mymap.insert(ft::pair<int, int>(3, 5));
			    mymap.insert(ft::pair<int, int>(4, 5));
			    mymap.insert(ft::pair<int, int>(5, 5));
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
