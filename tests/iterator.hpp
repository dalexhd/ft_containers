/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:24:51 by aborboll          #+#    #+#             */
/*   Updated: 2022/01/18 19:15:48 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/iterator.hpp"
#include "Tester.hpp"

class iterator_tester : public Tester
{
	private:
		bool	_status;
	public:
		iterator_tester(void) : Tester("iterator"), _status(true) {};
		void	setStatus(bool status) { _status = status; }
		bool	getStatus(void) { return (_status); }
		bool	test()
		{
			this->section("operators");
			this->expect("ft::reverse_iterator::operator++", [&]{
				//vector
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				std::string strvector = "";
				while (rev_from != rev_until) {
					strvector += std::to_string(*rev_from) + " ";
					++rev_from;
				}
				//map
				std::map<int, int> mymap;
				for (int i=0; i<10; i++) mymap.insert(std::pair<int, int>(i, i));
				typedef std::map<int, int>::iterator iter_typemap;
				iter_typemap frommap (mymap.begin());
				iter_typemap untilmap (mymap.end());
				ft::reverse_iterator<iter_typemap> rev_until_map (frommap);
				ft::reverse_iterator<iter_typemap> rev_from_map (untilmap);
				std::string strmap = "";
				while (rev_from_map != rev_until_map) {
					strmap += std::to_string(rev_from_map->first) + " ";
					++rev_from_map;
				}
				return (strvector == "9 8 7 6 5 4 3 2 1 0 " && strmap == "9 8 7 6 5 4 3 2 1 0 ");
			}, [&]{
				//vector
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				std::reverse_iterator<iter_type> rev_from (until);
				std::string strvector = "";
				while (rev_from != rev_until) {
					strvector += std::to_string(*rev_from) + " ";
					++rev_from;
				}
				//map
				std::map<int, int> mymap;
				for (int i=0; i<10; i++) mymap.insert(std::pair<int, int>(i, i));
				typedef std::map<int, int>::iterator iter_typemap;
				iter_typemap frommap (mymap.begin());
				iter_typemap untilmap (mymap.end());
				std::reverse_iterator<iter_typemap> rev_until_map (frommap);
				std::reverse_iterator<iter_typemap> rev_from_map (untilmap);
				std::string strmap = "";
				while (rev_from_map != rev_until_map) {
					strmap += std::to_string(rev_from_map->first) + " ";
					++rev_from_map;
				}
				return (strvector == "9 8 7 6 5 4 3 2 1 0 " && strmap == "9 8 7 6 5 4 3 2 1 0 ");
			});
			this->expect("ft::reverse_iterator::&operator++", [&]{
				//vector
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				std::string strvector = "";
				while (rev_from != rev_until)
					strvector += std::to_string(*(rev_from++)) + " ";
				//map
				std::map<int, int> mymap;
				for (int i=0; i<10; i++) mymap.insert(std::pair<int, int>(i, i));
				typedef std::map<int, int>::iterator iter_typemap;
				iter_typemap frommap (mymap.begin());
				iter_typemap untilmap (mymap.end());
				ft::reverse_iterator<iter_typemap> rev_until_map (frommap);
				ft::reverse_iterator<iter_typemap> rev_from_map (untilmap);
				std::string strmap = "";
				while (rev_from_map != rev_until_map) {
					strmap += std::to_string((rev_from_map++)->first) + " ";
				}
				return (strvector == "9 8 7 6 5 4 3 2 1 0 " && strmap == "9 8 7 6 5 4 3 2 1 0 ");
			}, [&]{
				//vector
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				std::reverse_iterator<iter_type> rev_from (until);
				std::string strvector = "";
				while (rev_from != rev_until)
					strvector += std::to_string(*(rev_from++)) + " ";
				//map
				std::map<int, int> mymap;
				for (int i=0; i<10; i++) mymap.insert(std::pair<int, int>(i, i));
				typedef std::map<int, int>::iterator iter_typemap;
				iter_typemap frommap (mymap.begin());
				iter_typemap untilmap (mymap.end());
				std::reverse_iterator<iter_typemap> rev_until_map (frommap);
				std::reverse_iterator<iter_typemap> rev_from_map (untilmap);
				std::string strmap = "";
				while (rev_from_map != rev_until_map) {
					strmap += std::to_string((rev_from_map++)->first) + " ";
				}
				return (strvector == "9 8 7 6 5 4 3 2 1 0 " && strmap == "9 8 7 6 5 4 3 2 1 0 ");
			});
			this->expect("ft::reverse_iterator::operator--", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				ft::reverse_iterator<iter_type> rev_begin (myvector.end());
				ft::reverse_iterator<iter_type> rev_end (myvector.begin());
				ft::reverse_iterator<iter_type> rev_iterator = rev_begin;
				std::string ret1 = "";
				std::string ret2 = "";
				while ( rev_iterator != rev_end )
				{
					ret1 += std::to_string(*rev_iterator) + " ";
					rev_iterator++;
				}
				while ( rev_iterator != rev_begin )
				{
					rev_iterator--;
					ret2 += std::to_string(*rev_iterator) + " ";
				}
				return (ret1 == "9 8 7 6 5 4 3 2 1 0 " && ret2 == "0 1 2 3 4 5 6 7 8 9 ");
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				std::reverse_iterator<iter_type> rev_begin (myvector.end());
				std::reverse_iterator<iter_type> rev_end (myvector.begin());
				std::reverse_iterator<iter_type> rev_iterator = rev_begin;
				std::string ret1 = "";
				std::string ret2 = "";
				while ( rev_iterator != rev_end )
				{
					ret1 += std::to_string(*rev_iterator) + " ";
					rev_iterator++;
				}
				while ( rev_iterator != rev_begin )
				{
					rev_iterator--;
					ret2 += std::to_string(*rev_iterator) + " ";
				}
				return (ret1 == "9 8 7 6 5 4 3 2 1 0 " && ret2 == "0 1 2 3 4 5 6 7 8 9 ");
			});
			this->expect("ft::reverse_iterator::&operator--", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				ft::reverse_iterator<iter_type> rev_begin (myvector.end());
				ft::reverse_iterator<iter_type> rev_end (myvector.begin());
				ft::reverse_iterator<iter_type> rev_iterator = rev_begin;
				std::string ret1 = "";
				std::string ret2 = "";
				while ( rev_iterator != rev_end )
					ret1 += std::to_string(*rev_iterator++) + " ";
				while ( rev_iterator != rev_begin )
					ret2 += std::to_string(*(--rev_iterator)) + " ";
				return (ret1 == "9 8 7 6 5 4 3 2 1 0 " && ret2 == "0 1 2 3 4 5 6 7 8 9 ");
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				std::reverse_iterator<iter_type> rev_begin (myvector.end());
				std::reverse_iterator<iter_type> rev_end (myvector.begin());
				std::reverse_iterator<iter_type> rev_iterator = rev_begin;
				std::string ret1 = "";
				std::string ret2 = "";
				while ( rev_iterator != rev_end )
					ret1 += std::to_string(*rev_iterator++) + " ";
				while ( rev_iterator != rev_begin )
					ret2 += std::to_string(*(--rev_iterator)) + " ";
				return (ret1 == "9 8 7 6 5 4 3 2 1 0 " && ret2 == "0 1 2 3 4 5 6 7 8 9 ");
			});
			this->expect("ft::reverse_iterator::operator*", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				std::string str = "";
				while (rev_from != rev_until)
					str += std::to_string(*rev_from++) + " ";
				return (str == "9 8 7 6 5 4 3 2 1 0 ");
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				std::string str = "";
				while (rev_from != rev_until)
					str += std::to_string(*rev_from++) + " ";
				return (str == "9 8 7 6 5 4 3 2 1 0 ");
			});

			this->expect("ft::reverse_iterator::operator[]", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				return (rev_until[2] == 7);
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				return (rev_until[2] == 7);
			});

			this->expect("ft::reverse_iterator::operator->", [&]{
				std::map<int,std::string> numbers;
				//TODO: Change to ft::make_pair
				numbers.insert(std::make_pair(1,"one"));
				numbers.insert(std::make_pair(2,"two"));
				numbers.insert(std::make_pair(3,"three"));
				typedef std::map<int,std::string>::iterator map_iter;
				ft::reverse_iterator<map_iter> rev_end (numbers.begin());
				ft::reverse_iterator<map_iter> rev_iterator (numbers.end());
				std::string str = "";
				for ( ; rev_iterator != rev_end ; ++rev_iterator )
					str += std::to_string((*rev_iterator).first) + " " + (*rev_iterator).second + " ";
				return (str == "3 three 2 two 1 one ");
			}, [&]{
				std::map<int,std::string> numbers;
				numbers.insert(std::make_pair(1,"one"));
				numbers.insert(std::make_pair(2,"two"));
				numbers.insert(std::make_pair(3,"three"));
				typedef std::map<int,std::string>::iterator map_iter;
				std::reverse_iterator<map_iter> rev_end (numbers.begin());
				std::reverse_iterator<map_iter> rev_iterator (numbers.end());
				std::string str = "";
				for ( ; rev_iterator != rev_end ; ++rev_iterator )
					str += std::to_string((*rev_iterator).first) + " " + (*rev_iterator).second + " ";
				return (str == "3 three 2 two 1 one ");
			});

			this->expect("ft::reverse_iterator::operator==", [&]{
				//Vector
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.begin());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				//Map
				std::map<int,std::string> numbers;
				numbers.insert(std::make_pair(1,"one"));
				numbers.insert(std::make_pair(2,"two"));
				numbers.insert(std::make_pair(3,"three"));
				typedef std::map<int,std::string>::iterator map_iter;
				map_iter frommap (numbers.begin());
				map_iter untilmap (numbers.end());
				ft::reverse_iterator<map_iter> rev_until_map (frommap);
				ft::reverse_iterator<map_iter> rev_from_map (untilmap);
				std::string str;
				while (rev_from_map != rev_until_map)
				{
					str += std::to_string((*rev_from_map).first) + " " + (*rev_from_map).second + " ";
					++rev_from_map;
				}
				return (rev_from_map == rev_until_map && str == "3 three 2 two 1 one ");
			}, [&]{
				//Vector
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.begin());
				std::reverse_iterator<iter_type> rev_until (from);
				std::reverse_iterator<iter_type> rev_from (until);
				//Map
				std::map<int,std::string> numbers;
				numbers.insert(std::make_pair(1,"one"));
				numbers.insert(std::make_pair(2,"two"));
				numbers.insert(std::make_pair(3,"three"));
				typedef std::map<int,std::string>::iterator map_iter;
				map_iter frommap (numbers.begin());
				map_iter untilmap (numbers.end());
				std::reverse_iterator<map_iter> rev_until_map (frommap);
				std::reverse_iterator<map_iter> rev_from_map (untilmap);
				std::string str;
				while (rev_from_map != rev_until_map)
				{
					str += std::to_string((*rev_from_map).first) + " " + (*rev_from_map).second + " ";
					++rev_from_map;
				}
				return (rev_from_map == rev_until_map && str == "3 three 2 two 1 one ");
			});

			this->expect("ft::reverse_iterator::operator!=", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_from != rev_until)
					result += std::to_string(*rev_from++);
				return (result == "9876543210");
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				std::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_from != rev_until)
					result += std::to_string(*rev_from++);
				return (result == "9876543210");
			});
			this->expect("ft::reverse_iterator::operator<", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_from < rev_until)
					result += std::to_string(*rev_from++);
				return (result == "9876543210");
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				std::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_from < rev_until)
					result += std::to_string(*rev_from++);
				return (result == "9876543210");
			});
			this->expect("ft::reverse_iterator::operator>", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_until > rev_from)
					result += std::to_string(*rev_from++);
				return (result == "9876543210");
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				std::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_until > rev_from)
					result += std::to_string(*rev_from++);
				return (result == "9876543210");
			});
			this->expect("ft::reverse_iterator::operator<=", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_from <= rev_until)
				{
					if (rev_from != rev_until)
						result += std::to_string(rev_from != rev_until ? *rev_from++ : *rev_from);
					else
						break ;
				}
				return (result == "9876543210");
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				std::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_from <= rev_until)
				{
					if (rev_from != rev_until)
						result += std::to_string(rev_from != rev_until ? *rev_from++ : *rev_from);
					else
						break ;
				}
				return (result == "9876543210");
			});
			this->expect("ft::reverse_iterator::operator>=", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_until >= rev_from)
				{
					if (rev_from != rev_until)
						result += std::to_string(rev_from != rev_until ? *rev_from++ : *rev_from);
					else
						break ;
				}
				return (result == "9876543210");
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				std::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_until >= rev_from)
				{
					if (rev_from != rev_until)
						result += std::to_string(rev_from != rev_until ? *rev_from++ : *rev_from);
					else
						break ;
				}
				return (result == "9876543210");
			});
			this->expect("ft::reverse_iterator::operator+", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back((i * 2));	// myvector: 0 2 4 6 8 10 12 14 16 18
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				ft::reverse_iterator<iter_type> rev_until (from);
				return (*(from + 5) == 10);
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back((i * 2));	// myvector: 0 2 4 6 8 10 12 14 16 18
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				std::reverse_iterator<iter_type> rev_until (from);
				return (*(from + 5) == 10);
			});
			this->expect("ft::reverse_iterator::operator-", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back((i * 2));	// myvector: 0 2 4 6 8 10 12 14 16 18
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				return (*(from - 6) == 8);
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back((i * 2));	// myvector: 0 2 4 6 8 10 12 14 16 18
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				return (*(from - 6) == 8);
			});
			this->expect("ft::reverse_iterator::operator+=", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back((i * 2));	// myvector: 0 2 4 6 8 10 12 14 16 18
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				ft::reverse_iterator<iter_type> rev_until (from);
				from += 5;
				return (*from == 10);
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back((i * 2));	// myvector: 0 2 4 6 8 10 12 14 16 18
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				std::reverse_iterator<iter_type> rev_until (from);
				from += 5;
				return (*from == 10);
			});
			this->expect("ft::reverse_iterator::operator-=", [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back((i * 2));	// myvector: 0 2 4 6 8 10 12 14 16 18
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				from -= 6;
				return (*from == 8);
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back((i * 2));	// myvector: 0 2 4 6 8 10 12 14 16 18
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				from -= 6;
				return (*from == 8);
			});
			this->endSection();
			return (true);
		}
};
