/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 12:18:28 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:02:43 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	append_map(t_drawer *drawer, t_map *new_map)
{
	if (!(drawer->map))
	{
		drawer->map = new_map;
		drawer->current = new_map;
		drawer->last = new_map;
		return ;
	}
	new_map->prev = drawer->last;
	drawer->last->next = new_map;
	drawer->last = new_map;
}

static char	**create_grid(t_drawer *drawer)
{
	char	**new_grid;
	int		i;

	if (!(new_grid = (char**)malloc(sizeof(char*) * drawer->nb_row)))
		return (NULL);
	ft_bzero(new_grid, sizeof(char**) * drawer->nb_row);
	i = -1;
	while (++i < drawer->nb_row)
	{
		if (!(new_grid[i] = (char*)malloc(sizeof(char) * drawer->nb_col)))
		{
			ft_free_split(new_grid);
			return (NULL);
		}
	}
	return (new_grid);
}

static int	fill_line(t_drawer *drawer, char *line, int y)
{
	int	i;
	int	x;

	i = 0;
	while (line[i] && line[i] != 'o' && line[i] != 'O' && line[i] != 'x'\
		&& line[i] != 'X' && line[i] != '.')
		i++;
	x = 0;
	while (line[i + x] && x < drawer->nb_col)
	{
		if (line[i + x] && line[i + x] != 'o' && line[i + x] != 'O'\
			&& line[i + x] != 'x' && line[i + x] != 'X' && line[i + x] != '.')
			return (1);
		if (line[i + x] == 'o' || line[i + x] == 'O')
			(drawer->last->p1_score)++;
		else if (line[i + x] == 'x' || line[i + x] == 'X')
			(drawer->last->p2_score)++;
		drawer->last->grid[y][x] = line[i + x];
		x++;
	}
	if (x != drawer->nb_col)
		return (1);
	return (0);
}

static int	fill_map(t_drawer *drawer)
{
	int	ret;
	int	y;

	y = -1;
	while (++y < drawer->nb_row)
	{
		ret = get_next_line2(0, &(drawer->line), &(drawer->join));
		if (ret <= 0)
			return (ret = 0 ? print_input_error(3) : print_sys_error(errno));
		if ((fill_line(drawer, drawer->line, y)))
			return (print_input_error(3));
		ft_strdel(&(drawer->line));
	}
	return (0);
}

int			map_manager(t_drawer *drawer, int same_map)
{
	t_map	*new_map;

	if (!(new_map = (t_map*)malloc(sizeof(t_map))))
		return (print_sys_error(errno));
	ft_bzero(new_map, sizeof(t_map));
	if (!(new_map->grid = create_grid(drawer)))
		return (print_sys_error(errno));
	append_map(drawer, new_map);
	if (!same_map)
		if (fill_map(drawer))
			return (1);
	return (0);
}
