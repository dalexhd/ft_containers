/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:16:18 by aborboll          #+#    #+#             */
/*   Updated: 2022/03/03 20:10:54 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
#define TESTER_H

/*
** Incluimos las librerias esenciales.
*/
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <vector>

#include "../includes/type_traits.hpp"
#include "colors.hpp"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <sys/time.h>
int64_t getNs()
{
	return mach_absolute_time();
}
#elif __linux__
#include <time.h>
long getNs()
{
	struct timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	return (time.tv_nsec);
}
#endif

class Tester
{
  private:
	size_t      _index;
	std::string _section;

  protected:
	std::string const _name;

  public:
	Tester(std::string const name) : _index(0), _name(name)
	{
		std::cout << std::endl << C_CYAN;
		for (int each = 0; each < 4; each++)
		{
			printf("\rStarting test for %s %.*s   \b\b\b", this->getName().c_str(), each, "...");
			fflush(stdout); // force printing as no newline in output
			usleep(50000);
		}
		std::cout << C_X << std::endl;
	}
	std::string getName() const
	{
		return (this->_name);
	}
	void section(std::string const name)
	{
		this->setSection(name);
		std::cout << "------------------------------------ " << C_BOLD << "Starting " << name << " section..." << C_X << " ------------------------------------" << std::endl;
	}
	void endSection()
	{
		std::cout << "------------------------------------ " << C_BOLD << "Ending " << this->getSection() << " section..." << C_X << " ------------------------------------" << std::endl;
		this->setSection("");
	}

	template <typename T = bool>
	bool expect(std::string const title, std::function<T()> &&fn, std::function<T()> &&ret)
	{
		long long fnDuration[10];
		long long retDuration[10];
		T         fnVal;
		T         retVal;

		int i = 0;
		while (i < 10)
		{
			long long fnstart = getNs();
			fnVal = fn();
			fnDuration[i] = getNs() - fnstart;
			long long retstart = getNs();
			retVal = ret();
			retDuration[i] = getNs() - retstart;
			i++;
			usleep(100);
		}
		long long fnMeanDuration = std::accumulate(std::begin(fnDuration), std::end(fnDuration), 0, std::plus<long long>()) / sizeof(fnDuration) / sizeof(fnDuration[0]);
		long long retMeanDuration = std::accumulate(std::begin(retDuration), std::end(retDuration), 0, std::plus<long long>()) / sizeof(retDuration) / sizeof(retDuration[0]);
		retMeanDuration = retMeanDuration == 0 ? 1 : retMeanDuration;
		double slowerRatio = fnMeanDuration / retMeanDuration;

		if (fnVal != retVal)
		{
			std::cerr << C_WHITE << "[" << this->getName() << "]"
			          << "[" << this->getIndex() << "]" << C_RED << " (" << title << ") test not passed 💣" << C_X << " [🙋" << fnMeanDuration << "ns / 🌐" << retMeanDuration << "ns] (" << slowerRatio << " slower)" << C_X << std::endl;
			this->setStatus(false);
		}
		else if (slowerRatio >= 20)
		{
			std::cerr << C_WHITE << "[" << this->getName() << "]"
			          << "[" << this->getIndex() << "]" << C_RED << " (" << title << ") test not passed ⌛" << C_X << " [🙋" << fnMeanDuration << "ns / 🌐" << retMeanDuration << "ns] (" << slowerRatio << " slower)" << C_X << std::endl;
			this->setStatus(false);
		}
		else
			std::cout << C_WHITE << "[" << this->getName() << "]"
			          << "[" << this->getIndex() << "]" << C_GREEN << " (" << title << ") test passed 🚀" << C_X << " [🙋" << fnMeanDuration << "ns / 🌐" << retMeanDuration << "ns] (" << slowerRatio << " slower)" << C_X << std::endl;
		this->setIndex(this->getIndex() + 1);
		usleep(1000);
		return (this->getStatus());
	}

	void setIndex(size_t index)
	{
		_index = index;
	}
	size_t getIndex() const
	{
		return (_index);
	}
	std::string getSection() const
	{
		return (_section);
	}
	void setSection(std::string section)
	{
		_section = section;
	}
	virtual bool test(void) = 0;
	virtual void setStatus(bool status) = 0;
	virtual bool getStatus() = 0;
	virtual ~Tester()
	{
		std::cout << C_CYAN "--- Finishing test for " << this->getName() << C_X << " ---" << std::endl;
		usleep(100000);
	}
};

#endif
