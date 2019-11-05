/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 14:36:11 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 17:51:40 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		print_sys_error(int errnum)
{
	ft_putstr_fd("visu : error : ", 2);
	ft_putstr_fd(strerror(errnum), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int		print_sdl_error(int errnum)
{
	ft_putstr_fd("visu : SDL error : ", 2);
	if (errnum == 1)
		ft_putstr_fd("Unable to initialize SDL.\n", 2);
	if (errnum == 2)
		ft_putstr_fd("Unable to create an SDL window.\n", 2);
	if (errnum == 3)
		ft_putstr_fd("Unable to create renderer.\n", 2);
	if (errnum == 4)
		ft_putstr_fd("Unable to load font.\n", 2);
	if (errnum == 5)
		ft_putstr_fd("Unable to initialize TTF.\n", 2);
	return (1);
}

int		print_input_error(int errnum)
{
	ft_putstr_fd("visu : ", 2);
	if (errnum == 1)
		ft_putstr_fd("Wrong input.\n", 2);
	else if (errnum == 2)
		ft_putstr_fd("Wrong map dimensions.\n", 2);
	else if (errnum == 3)
		ft_putstr_fd("Wrong map.\n", 2);
	else if (errnum == 4)
		ft_putstr_fd("Wrong piece.\n", 2);
	else if (errnum == 5)
		ft_putstr_fd("Wrong player.\n", 2);
	else if (errnum == 6)
		ft_putstr_fd("max rows = MAX_ROW || max_cols = MAX_COL.\n", 2);
	return (1);
}
