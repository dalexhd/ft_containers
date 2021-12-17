/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:16:18 by aborboll          #+#    #+#             */
/*   Updated: 2021/12/17 00:00:33 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

/*
** Incluimos las librerias esenciales.
*/
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "colors.hpp"

class Tester
	{
		private:
			size_t	_index;
			std::string	_section;
		protected:
			std::string const _name;
		public:
			Tester(std::string const name) : _index(0), _name(name)
			{
				std::cout << C_CYAN;
				for (int each = 0; each < 4; each++)
				{
					printf("\rStarting test for %s %.*s   \b\b\b", this->getName().c_str(), each, "...");
					fflush(stdout);//force printing as no newline in output
					usleep(250000);
				}
				std::cout << C_X << std::endl;
			}
			std::string	getName() const {
				return (this->_name);
			}
			template <typename T, typename E>
			bool	expect(std::string const title, T (fn), E ret)
			{
				if (fn != ret)
				{
					std::cerr << C_WHITE << "[" << this->getName()  << "]" << "[" << this->getIndex() << "]" << C_RED << " (" << title << ") test not passed 💣" << C_X << std::endl;
					this->setStatus(false);
				}
				else
					std::cout << C_WHITE << "[" << this->getName()  << "]" << "[" << this->getIndex()  << "]" << C_GREEN << " (" << title << ") test passed 🚀" << C_X << std::endl;
				this->setIndex(this->getIndex() + 1);
				usleep(50000);
				return (this->getStatus());
			}
			void	section(std::string const name)
			{
				this->setSection(name);
				std::cout << "------------------------------------ " << C_BOLD << "Starting " << name << " section..." << C_X << " ------------------------------------" << std::endl;
			}
			void	endSection()
			{
				std::cout << "------------------------------------ " << C_BOLD << "Ending " << this->getSection() << " section..." << C_X << " ------------------------------------" << std::endl;
				this->setSection("");
			}
			template <typename T>
			bool	expect(void (*fn)(int), T &ret)
			{
				return ((*fn) == ret);
			}
			void	setIndex(size_t index)
			{
				_index = index;
			}
			size_t	getIndex() const
			{
				return (_index);
			}
			std::string	getSection() const
			{
				return (_section);
			}
			void	setSection(std::string section)
			{
				_section = section;
			}
			virtual bool test(void) = 0;
			virtual void setStatus(bool status) = 0;
			virtual bool getStatus() = 0;
			virtual ~Tester() {
				std::cout << C_CYAN "--- Finishing test for " << this->getName() << C_X << " ---" << std::endl;
				usleep(100000);
			}
	};

#endif

