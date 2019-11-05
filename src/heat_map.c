/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:26:19 by rkirszba          #+#    #+#             */
/*   Updated: 2019/08/07 17:03:39 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	new_elem_manager(t_queue **queue, int x, int y)
{
	t_queue	*new;
	t_queue	*current;

	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		return (print_sys_error(errno));
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (!(*queue))
	{
		*queue = new;
		return (0);
	}
	current = *queue;
	while (current->next)
		current = current->next;
	current->next = new;
	return (0);
}

static int	map_browser(t_filler *filler)
{
	int	x;
	int	y;
	int	x_shft;
	int	y_shft;

	x = filler->queue->x;
	y = filler->queue->y;
	x_shft = -2;
	while (++x_shft < 2)
	{
		y_shft = -2;
		while (++y_shft < 2)
			if (!(!x_shft && !y_shft)\
					&& x + x_shft >= 0 && x + x_shft < filler->map_col\
					&& y + y_shft >= 0 && y + y_shft < filler->map_row\
					&& filler->heat_map[y + y_shft][x + x_shft] == 0)
			{
				filler->heat_map[y + y_shft][x + x_shft] =\
					filler->heat_map[y][x] >= 0 ?\
						filler->heat_map[y][x] + 1 : 1;
				if (new_elem_manager(&(filler->queue), x + x_shft, y + y_shft))
					return (1);
			}
	}
	return (0);
}

static int	contour_checker(t_filler *filler, int x, int y)
{
	int	x_shft;
	int	y_shft;

	filler->heat_map[y][x] = -3;
	x_shft = -2;
	while (++x_shft < 2)
	{
		y_shft = -2;
		while (++y_shft < 2)
			if (!(!x_shft && !y_shft)\
					&& x + x_shft >= 0 && x + x_shft < filler->map_col\
					&& y + y_shft >= 0 && y + y_shft < filler->map_row)
			{
				if (filler->heat_map[y][x] != -4\
					&& filler->heat_map[y + y_shft][x + x_shft] == 0)
					if ((filler->heat_map[y][x] = -4)\
							&& new_elem_manager(&(filler->queue), x, y))
						return (1);
				if (filler->heat_map[y + y_shft][x + x_shft]\
					== (filler->player_nb == 1 ? -2 : -1))
					if (contour_checker(filler, x + x_shft, y + y_shft))
						return (1);
			}
	}
	return (0);
}

static int	contour_manager(t_filler *filler)
{
	int		x;
	int		y;
	int		stop;

	stop = 0;
	y = -1;
	while (!stop && ++y < filler->map_row)
	{
		x = -1;
		while (!stop && ++x < filler->map_col)
			if (filler->heat_map[y][x] == (filler->player_nb == 1 ? -2 : -1))
				stop = 1;
	}
	if (stop && contour_checker(filler, x, y))
		return (1);
	return (0);
}

int			heat_map_filler(t_filler *filler)
{
	t_queue *tmp;

	if (map_reader(filler))
		return (1);
	if (contour_manager(filler))
		return (1);
	while (filler->queue)
	{
		if (map_browser(filler))
			return (1);
		tmp = filler->queue;
		filler->queue = filler->queue->next;
		free(tmp);
	}
	return (0);
}
