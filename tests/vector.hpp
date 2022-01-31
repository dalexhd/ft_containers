/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:28:42 by aborboll          #+#    #+#             */
/*   Updated: 2022/01/31 21:54:40 by aborboll         ###   ########.fr       */
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
			this->section("member functions");
			this->expect("vector::at", [&]{
				ft::vector<int> myvector;
				myvector.assign(10, 42);
				return myvector.at(8) == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (myvector.at(8) == 42);
			});
			this->expect("vector::at catch(out_of_range)", [&]{
				try
				{
					ft::vector<int> myvector;
					myvector.assign(10, 42);
					return myvector.at(11) == 42;
				}
				catch(const std::exception& e)
				{
					return (true);
				}
			}, [&]{
				try
				{
					std::vector<int> myvector;
					myvector.assign(10, 42);
					return myvector.at(11) == 42;
				}
				catch(const std::out_of_range& e)
				{
					return (true);
				}
			});
			this->expect("vector::back", [&]{
				ft::vector<int> myvector;
				myvector.assign(10, 42);
				return myvector.back() == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return myvector.back() == 42;
			});
			this->expect("vector::begin", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return *(myvector.begin()) == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return *(myvector.begin()) == 42;
			});
			this->expect("vector::clear", [&]{
				ft::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.clear();
				return (myvector.empty());
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.clear();
				return (myvector.empty());
			});
			this->expect("vector::empty", [&]{
				ft::vector<int> myvector;
				myvector.assign(10, 42);
				return !myvector.empty();
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (!myvector.empty());
			});
			this->expect("vector::end", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return *(myvector.end() - 1) == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (*(myvector.end() - 1) == 42);
			});
			this->expect("vector::erase", [&] {
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.erase(myvector.begin() + 5);
				return (false);
				//return myvector.size() == 9;
			}, [&] {
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.erase(myvector.begin() + 5);
				return (myvector.size() == 9);
			});
			this->expect("vector::front", [&]{
				ft::vector<int> myvector;
				myvector.assign(10, 42);
				return myvector.front() == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (myvector.front() == 42);
			});
			this->expect("vector::get_allocator", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return myvector.get_allocator() == std::allocator<int>();
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (myvector.get_allocator() == std::allocator<int>());
			});
			this->expect("vector::insert", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.insert(myvector.begin() + 5, 42);
				return (false);
				//return myvector.size() == 11;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.insert(myvector.begin() + 5, 42);
				return (myvector.size() == 11);
			});
			this->expect("vector::max_size", [&]{
				ft::vector<int> myvector;
				return myvector.max_size() == ft::vector<int>().max_size();
			}, [&]{
				std::vector<int> myvector;
				return (myvector.max_size() == std::vector<int>().max_size());
			});
			this->expect("vector::pop_back", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.pop_back();
				return (false);
				//return myvector.size() == 9;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.pop_back();
				return (myvector.size() == 9);
			});
			this->expect("vector::push_back", [&]{
				ft::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.push_back(24);
				return (myvector.size() == 11 && myvector.back() == 24);
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.push_back(24);
				return (myvector.size() == 11 && myvector.back() == 24);
			});
			this->expect("vector::rbegin", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return *(myvector.rbegin()) == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (*(myvector.rbegin()) == 42);
			});
			this->expect("vector::rend", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return *(myvector.rend() - 1) == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (*(myvector.rend() - 1) == 42);
			});
			this->expect("vector::reserve", [&]{
				ft::vector<int> myvector;
				myvector.reserve(42);
				return (myvector.capacity() == 42);
			}, [&]{
				std::vector<int> myvector;
				myvector.reserve(42);
				return (myvector.capacity() == 42);
			});
			this->expect("vector::reserve catch(length_error)", [&]{
				try
				{
					ft::vector<int> myvector;
					myvector.reserve(myvector.max_size() + 1);
					return (false);
				}
				catch(const std::length_error& e)
				{
					return (true);
				}
			}, [&]{
				try
				{
					std::vector<int> myvector;
					myvector.reserve(myvector.max_size() + 1);
					return (false);
				}
				catch(const std::length_error& e)
				{
					return (true);
				}
			});
			this->expect("vector::resize", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.resize(42);
				return (false);
				//return myvector.size() == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.resize(42);
				return (myvector.size() == 42);
			});
			this->expect("vector::size", [&]{
				ft::vector<int> myvector;
				myvector.push_back(1);
				myvector.push_back(2);
				myvector.push_back(3);
				return (myvector.size() == 3);
			}, [&]{
				std::vector<int> myvector;
				myvector.push_back(1);
				myvector.push_back(2);
				myvector.push_back(3);
				return (myvector.size() == 3);
			});
			this->expect("vector::swap", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				std::vector<int> myvector2;
				myvector2.assign(10, 42);
				myvector.swap(myvector2);
				return (false);
				//return myvector.size() == 10 && myvector2.size() == 10;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				std::vector<int> myvector2;
				myvector2.assign(10, 42);
				myvector.swap(myvector2);
				return (myvector.size() == 10 && myvector2.size() == 10);
			});
			this->endSection();
			return (_status);
		}
};
