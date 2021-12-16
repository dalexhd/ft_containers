/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:36:41 by aborboll          #+#    #+#             */
/*   Updated: 2021/12/16 19:43:51 by aborboll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Incluimos las librerias esenciales.
*/
#include <iostream>
#include <string.h>

#include "tests/templates/is_integral.hpp"
bool	exit_status = 0;

int main(void)
{
	Tester * tests[] = { new is_integral_tester() };

	for (size_t i = 0; i < 1; i++)
	{
		if (!tests[i]->test())
			exit_status = 1;
		delete tests[i];
	}
	return (exit_status);
}
