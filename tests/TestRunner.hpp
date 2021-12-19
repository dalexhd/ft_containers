/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestRunner.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:16:18 by aborboll          #+#    #+#             */
/*   Updated: 2021/12/19 16:30:30 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H

#include "type_traits.hpp"
#include "utility.hpp"
#include "algorithm.hpp"

class TestRunner
	{
		private:
			bool	_status;
		public:
			TestRunner() {
				setStatus(true);
			};
			bool	run(void)
			{
				Tester * type_traits_test = new type_traits_tester();
				if (!type_traits_test->test()) setStatus(false);
				delete type_traits_test;

				Tester * utility_test = new utility_tester();
				if (!utility_test->test()) setStatus(false);
				delete utility_test;

				Tester * algorithm_test = new algorithm_tester();
				if (!algorithm_test->test()) setStatus(false);
				delete algorithm_test;

				return (getStatus());
			};
			void	setStatus(bool status)
			{
				_status = status;
			};
			bool	getStatus(void)	const
			{
				return (_status);
			};
			~TestRunner()
			{
				std::cout << std::endl << std::endl << std::endl;;
				if (!getStatus())
					std::cout <<  "-------------------------------- " << C_RED <<  "Tester finished with some errors... 💣" << C_X " --------------------------------" << std::endl;
				else
					std::cout <<  "-------------------------------- " << C_GREEN << "Yeah!!! Tester finished without any errors 🚀" << C_X " --------------------------------" << std::endl;
			}
	};

#endif

