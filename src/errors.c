/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:52:33 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/24 18:56:57 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		print_sys_error(int errnum)
{
	ft_putstr_fd("rkirszba.filler : error : ", 2);
	ft_putstr_fd(strerror(errnum), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int		print_input_error(int errnum)
{
	ft_putstr_fd("rkirszba.filler : ", 2);
	if (errnum == 1)
		ft_putstr_fd("Wrong player number.\n", 2);
	else if (errnum == 2)
		ft_putstr_fd("Wrong plateau description format.\n", 2);
	else if (errnum == 3)
		ft_putstr_fd("Wrong number of rows or columns.\n", 2);
	else if (errnum == 4)
		ft_putstr_fd("The number of columns doesn't match.\n", 2);
	else if (errnum == 5)
		ft_putstr_fd("The number of rows doesn't match.\n", 2);
	else if (errnum == 6)
		ft_putstr_fd("Bad character in the map.\n", 2);
	else if (errnum == 7)
		ft_putstr_fd("Wrong piece description format.\n", 2);
	else if (errnum == 8)
		ft_putstr_fd("Bad character in the piece.\n", 2);
	else if (errnum == 9)
		ft_putstr_fd("Wrong player number format.\n", 2);
	return (1);
}
