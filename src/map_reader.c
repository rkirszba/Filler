/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:09:24 by rkirszba          #+#    #+#             */
/*   Updated: 2019/08/07 17:03:40 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	generate_map(t_filler *filler, char *line)
{
	int	i;

	i = 8;
	if ((filler->map_row = get_num(line, &i)) <= 0\
			|| (filler->map_col = get_num(line, &i)) <= 0)
		return (print_input_error(2));
	if (!(filler->heat_map = (int**)malloc(sizeof(int*) * filler->map_row)))
		return (print_sys_error(errno));
	ft_bzero(filler->heat_map, sizeof(int*) * filler->map_row);
	i = -1;
	while (++i < filler->map_row)
		if (!(filler->heat_map[i] = (int*)malloc(sizeof(int)\
					* filler->map_col)))
		{
			free_heat_map(filler);
			return (print_sys_error(errno));
		}
	return (0);
}

static int	map_header_checker(t_filler *filler)
{
	char	*line;
	int		ret;
	int		i;

	line = NULL;
	ret = get_next_line2(0, &line, &(filler->join));
	if (!ret || ret == -1)
		return (!ret ? 2 : print_sys_error(errno));
	if ((ret = ft_strncmp("Plateau ", line, 8)))
		print_input_error(2);
	if (!ret && filler->state == 1)
		ret = generate_map(filler, line);
	else if (!ret)
	{
		i = 8;
		if ((ret = (get_num(line, &i) != filler->map_row\
				|| get_num(line, &i) != filler->map_col)))
			print_input_error(3);
	}
	free(line);
	return (ret ? 1 : 0);
}

static int	fill_map_line(t_filler *filler, char *line, int y)
{
	int	i;
	int	x;

	i = 0;
	while (line[i] && line[i] != '.' && line[i] != 'x' && line[i] != 'X'\
		&& line[i] != 'o' && line[i] != 'O')
		i++;
	x = -1;
	while (line[i + (++x)] && x < filler->map_col)
	{
		if (line[i + x] == '.')
			filler->heat_map[y][x] = 0;
		else if (line[i + x] == 'o' || line[i + x] == 'O')
			filler->heat_map[y][x] = -1;
		else if (line[i + x] == 'x' || line[i + x] == 'X')
			filler->heat_map[y][x] = -2;
		else
			return (print_input_error(6));
	}
	return (x != filler->map_col || line[i + x] != 0 ?
			print_input_error(4) : 0);
}

int			map_reader(t_filler *filler)
{
	int		ret;
	int		y;
	char	*line;

	if ((ret = map_header_checker(filler)))
		return (ret);
	filler->state = 2;
	line = NULL;
	if ((ret = get_next_line2(0, &line, &(filler->join))) <= 0)
		return (ret == 0 ? print_input_error(5) : print_sys_error(errno));
	free(line);
	y = -1;
	while (++y < filler->map_row\
		&& (ret = get_next_line2(0, &line, &(filler->join))))
	{
		if (ret == -1)
			return (print_sys_error(errno));
		ret = fill_map_line(filler, line, y);
		free(line);
		if (ret)
			return (1);
	}
	if (y != filler->map_row)
		return (print_input_error(5));
	return (0);
}
