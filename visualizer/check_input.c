/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 21:49:10 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:11:39 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int			get_num(char *line, int *i)
{
	int	nb;

	while (line[*i] && line[*i] == ' ')
		(*i)++;
	nb = ft_atoi(line + *i);
	while (line[*i] && line[*i] != ' ')
		(*i)++;
	return (nb);
}

static int	check_end(t_drawer *drawer)
{
	int	ret;

	ret = 1;
	if (drawer->state == 0)
		ret = get_next_line2(0, &(drawer->line), &(drawer->join));
	drawer->state = 1;
	if (ret <= 0)
		return (ret == 0 ? print_input_error(1) : print_sys_error(errno));
	if (!ft_strncmp(drawer->line, "== O fin: ", 10))
		drawer->p1_score = ft_atoi(drawer->line + 10);
	else
		return (0);
	ft_strdel(&(drawer->line));
	ret = get_next_line2(0, &(drawer->line), &(drawer->join));
	if (ret == -1)
		return (print_sys_error(errno));
	if (ret == 0)
		return (print_input_error(1));
	if (!(ret = ft_strncmp(drawer->line, "== X fin: ", 10)))
		drawer->p2_score = ft_atoi(drawer->line + 10);
	ft_strdel(&(drawer->line));
	drawer->end = (ret == 0 ? 1 : 0);
	drawer->last->last = (ret == 0 ? 1 : 0);
	return (ret == 0 ? 0 : print_input_error(1));
}

static int	check_map_header(t_drawer *drawer)
{
	int nb_row;
	int	nb_col;
	int	i;
	int	ret;

	if ((ft_strncmp(drawer->line, "Plateau ", 8)))
		return (print_input_error(2));
	i = 8;
	nb_row = get_num(drawer->line, &i);
	if (nb_row <= 0 || (drawer->nb_row > 0 && drawer->nb_row != nb_row))
		return (print_input_error(2));
	nb_col = get_num(drawer->line, &i);
	if (nb_col <= 0 || (drawer->nb_col > 0 && drawer->nb_col != nb_col))
		return (print_input_error(2));
	drawer->nb_row = nb_row;
	drawer->nb_col = nb_col;
	ft_strdel(&(drawer->line));
	ret = get_next_line2(0, &(drawer->line), &(drawer->join));
	if (ret <= 0)
		return (ret = 0 ? print_input_error(3) : print_sys_error(errno));
	ft_strdel(&(drawer->line));
	return (0);
}

static int	check_actual_player(t_drawer *drawer)
{
	int	ret;

	ret = get_next_line2(0, &(drawer->line), &(drawer->join));
	if (ret <= 0)
		return (ret = 0 ? print_input_error(5) : print_sys_error(errno));
	if (ft_strlen(drawer->line) < 7)
		return (print_input_error(5));
	if ((ft_strncmp(drawer->line, "<got (", 6)))
		return (print_input_error(5));
	if (drawer->line[6] == 'O')
		drawer->last->player = 1;
	else if (drawer->line[6] == 'X')
		drawer->last->player = 2;
	else
		return (print_input_error(5));
	ft_strdel(&(drawer->line));
	return (0);
}

int			check_input(t_drawer *drawer)
{
	int	ret;

	if ((check_end(drawer)))
		return (1);
	if (drawer->end)
		return (0);
	if ((check_map_header(drawer)))
		return (1);
	if ((map_manager(drawer, 0)))
		return (1);
	if ((check_piece(drawer, 0)))
		return (1);
	if ((check_actual_player(drawer)))
		return (1);
	if ((ret = check_second_piece(drawer)) == 1)
		return (1);
	if (ret == 2)
	{
		if ((check_actual_player(drawer)))
			return (1);
		drawer->state = 0;
	}
	return (0);
}
