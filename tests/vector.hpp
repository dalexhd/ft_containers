/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:28:42 by aborboll          #+#    #+#             */
/*   Updated: 2022/01/20 20:25:06 by aborboll         ###   ########.fr       */
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
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return myvector.at(5) == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (myvector.at(5) == 42);
			});
			this->expect("vector::back", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return myvector.back() == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (myvector.back() == 42);
			});
			this->expect("vector::begin", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return *(myvector.begin()) == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (*(myvector.begin()) == 42);
			});
			this->expect("vector::clear", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.clear();
				return (false);
				//return myvector.empty();
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.clear();
				return (myvector.empty());
			});
			this->expect("vector::empty", [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return !myvector.empty();
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
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return myvector.front() == 42;
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
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return myvector.max_size() == std::vector<int>().max_size();
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
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
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.push_back(42);
				return (false);
				//return myvector.size() == 11;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.push_back(42);
				return (myvector.size() == 11);
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
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.reserve(42);
				return (false);
				//return myvector.capacity() == 42;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				myvector.reserve(42);
				return (myvector.capacity() == 42);
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
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (false);
				//return myvector.size() == 10;
			}, [&]{
				std::vector<int> myvector;
				myvector.assign(10, 42);
				return (myvector.size() == 10);
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
