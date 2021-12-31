/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:37:03 by aborboll          #+#    #+#             */
/*   Updated: 2021/12/31 16:27:50 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.hpp"
#include "Tester.hpp"
#include <stack>

class stack_tester : public Tester
{
	private:
		bool	_status;
	public:
		stack_tester(void) : Tester("stack"), _status(true) {};
		void	setStatus(bool status) { _status = status; }
		bool	getStatus(void) { return (_status); }
		bool	test()
		{
			this->section("empty");
			this->expect("empty true", [&]{
				ft::stack<int> mystack;
				return mystack.empty();
			}, [&]{
				std::stack<int> mystack;
				return mystack.empty();
			});
			this->expect("empty false", [&]{
				ft::stack<int> mystack;
				mystack.push(10);
				return mystack.empty();
			}, [&]{
				std::stack<int> mystack;
				mystack.push(10);
				return mystack.empty();
			});
			this->endSection();

			this->section("size");
			this->expect("size 0", [&]{
				ft::stack<int> mystack;
				return mystack.size();
			}, [&]{
				std::stack<int> mystack;
				return mystack.size();
			});
			this->expect("size 1", [&]{
				ft::stack<int> mystack;
				mystack.push(10);
				return mystack.size() == 1;
			}, [&]{
				std::stack<int> mystack;
				mystack.push(10);
				return mystack.size() == 1;
			});
			this->endSection();

			this->section("top");
			this->expect("top", [&]{
				ft::stack<int> mystack;
				mystack.push(10);
				mystack.push(20);
				mystack.top() -= 5;
				return mystack.top();
			}, [&]{
				std::stack<int> mystack;
				mystack.push(10);
				mystack.push(20);
				mystack.top() -= 5;
				return mystack.top();
			});
			this->endSection();

			this->section("push");
			this->expect("top", [&]{
				ft::stack<int> mystack;
				for (int i=0; i<5; ++i) mystack.push(i);
				return mystack.top() == 4;
			}, [&]{
				std::stack<int> mystack;
				for (int i=0; i<5; ++i) mystack.push(i);
				return mystack.top() == 4;
			});
			this->expect("top with pop", [&]{
				ft::stack<int> mystack;
				for (int i=0; i<5; ++i) mystack.push(i);
				mystack.pop();
				return mystack.top() == 3;
			}, [&]{
				std::stack<int> mystack;
				for (int i=0; i<5; ++i) mystack.push(i);
				mystack.pop();
				return mystack.top() == 3;
			});
			this->endSection();

			this->section("operators");
/* 			this->expect("==", [&]{
				ft::stack<int> mystack;
				ft::stack<int> mystack2;
				for (int i=0; i<5; ++i) mystack.push(i);
				for (int i=0; i<5; ++i) mystack2.push(i);
				return mystack == mystack2;
			}, [&]{
				std::stack<int> mystack;
				std::stack<int> mystack2;
				for (int i=0; i<5; ++i) mystack.push(i);
				for (int i=0; i<5; ++i) mystack2.push(i);
				return mystack == mystack2;
			}); */
			this->expect("!=", [&]{
				ft::stack<int> mystack;
				ft::stack<int> mystack2;
				for (int i=0; i<5; ++i) mystack.push(i);
				for (int i=0; i<4; ++i) mystack2.push(i);
				return mystack != mystack2;
			}, [&]{
				std::stack<int> mystack;
				std::stack<int> mystack2;
				for (int i=0; i<5; ++i) mystack.push(i);
				for (int i=0; i<4; ++i) mystack2.push(i);
				return mystack != mystack2;
			});
			this->expect("<", [&]{
				ft::stack<int> mystack;
				ft::stack<int> mystack2;
				for (int i=0; i<4; ++i) mystack.push(i);
				for (int i=0; i<5; ++i) mystack2.push(i);
				return mystack < mystack2;
			}, [&]{
				std::stack<int> mystack;
				std::stack<int> mystack2;
				for (int i=0; i<4; ++i) mystack.push(i);
				for (int i=0; i<5; ++i) mystack2.push(i);
				return mystack < mystack2;
			});
			this->expect("<=", [&]{
				ft::stack<int> mystack;
				ft::stack<int> mystack2;
				ft::stack<int> mystack3;
				for (int i=0; i<5; ++i) mystack.push(i);
				for (int i=0; i<5; ++i) mystack2.push(i);
				for (int i=0; i<6; ++i) mystack3.push(i);
				return mystack < mystack2 && !(mystack2 < mystack3);
			}, [&]{
				std::stack<int> mystack;
				std::stack<int> mystack2;
				std::stack<int> mystack3;
				for (int i=0; i<5; ++i) mystack.push(i);
				for (int i=0; i<5; ++i) mystack2.push(i);
				for (int i=0; i<6; ++i) mystack3.push(i);
				return mystack < mystack2 && !(mystack2 < mystack3);
			});
			this->expect(">", [&]{
				ft::stack<int> mystack;
				ft::stack<int> mystack2;
				for (int i=0; i<5; ++i) mystack.push(i);
				for (int i=0; i<4; ++i) mystack2.push(i);
				return mystack > mystack2;
			}, [&]{
				std::stack<int> mystack;
				std::stack<int> mystack2;
				for (int i=0; i<5; ++i) mystack.push(i);
				for (int i=0; i<4; ++i) mystack2.push(i);
				return mystack > mystack2;
			});

			this->expect(">=", [&]{
				ft::stack<int> mystack;
				ft::stack<int> mystack2;
				ft::stack<int> mystack3;
				for (int i=0; i<5; ++i) mystack.push(i);
				for (int i=0; i<5; ++i) mystack2.push(i);
				for (int i=0; i<6; ++i) mystack3.push(i);
				return mystack >= mystack2 && mystack3 >= mystack2;
			}, [&]{
				std::stack<int> mystack;
				std::stack<int> mystack2;
				std::stack<int> mystack3;
				for (int i=0; i<5; ++i) mystack.push(i);
				for (int i=0; i<5; ++i) mystack2.push(i);
				for (int i=0; i<6; ++i) mystack3.push(i);
				return mystack >= mystack2 && mystack3 >= mystack2;
			});
			this->endSection();
			return (_status);
		}
};
