/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:24:51 by aborboll          #+#    #+#             */
/*   Updated: 2022/01/16 20:02:01 by aborboll         ###   ########.fr       */
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
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				std::string str = "";
				while (rev_from != rev_until) {
					str += std::to_string(*rev_from) + " ";
					++rev_from;
				}
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
				while (rev_from != rev_until) {
					str += std::to_string(*rev_from) + " ";
					++rev_from;
				}
				return (str == "9 8 7 6 5 4 3 2 1 0 ");
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
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.begin());
				ft::reverse_iterator<iter_type> rev_until (from);
				ft::reverse_iterator<iter_type> rev_from (until);
				return (rev_from == rev_until);
			}, [&]{
 				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.begin());
				std::reverse_iterator<iter_type> rev_until (from);
				std::reverse_iterator<iter_type> rev_from (until);
				return (rev_from == rev_until);
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
				while (rev_from > rev_until)
					result += std::to_string(*rev_from++);
				return (result == "876543210");
			}, [&]{
				std::vector<int> myvector;
				for (int i=0; i<10; i++) myvector.push_back(i);
				typedef std::vector<int>::iterator iter_type;
				iter_type from (myvector.begin());
				iter_type until (myvector.end());
				std::reverse_iterator<iter_type> rev_until (from);
				std::reverse_iterator<iter_type> rev_from (until);
				std::string result;
				while (rev_from > rev_until)
					result += std::to_string(*rev_from++);
				return (result == "876543210");
			});
			this->expect("ft::reverse_iterator::operator>", [&]{
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
				return (true);
			}, [&]{
				return (false);
			});
			this->expect("ft::reverse_iterator::operator>=", [&]{
				return (true);
			}, [&]{
				return (false);
			});
			this->expect("ft::reverse_iterator::operator+", [&]{
				return (true);
			}, [&]{
				return (false);
			});
			this->expect("ft::reverse_iterator::operator-", [&]{
				return (true);
			}, [&]{
				return (false);
			});
			this->expect("ft::reverse_iterator::operator+=", [&]{
				return (true);
			}, [&]{
				return (false);
			});
			this->expect("ft::reverse_iterator::operator-=", [&]{
				return (true);
			}, [&]{
				return (false);
			});
			this->endSection();
			return (true);
		}
};
