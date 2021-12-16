/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aborboll <aborboll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:36:41 by aborboll          #+#    #+#             */
/*   Updated: 2021/12/16 21:04:38 by aborboll         ###   ########.fr       */
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

	size_t	i = 0;

	while (i < 1)
	{
		if (!tests[i]->test())
			exit_status = 1;
		delete tests[i];
		i++;
	}

	return (exit_status);
}
