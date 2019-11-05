/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:17:29 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:07:09 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static char	**create_piece(t_drawer *drawer)
{
	char	**new_piece;
	int		i;

	if (!(new_piece = (char**)malloc(sizeof(char*) * drawer->last->piece_row)))
		return (NULL);
	ft_bzero(new_piece, sizeof(char*) * drawer->last->piece_row);
	i = -1;
	while (++i < drawer->last->piece_row)
	{
		if (!(new_piece[i] = (char*)malloc(sizeof(char)\
					* drawer->last->piece_col)))
		{
			ft_free_split(new_piece);
			return (NULL);
		}
	}
	return (new_piece);
}

static int	fill_piece(t_drawer *drawer)
{
	int	ret;
	int	x;
	int	y;

	y = -1;
	while (++y < drawer->last->piece_row)
	{
		ret = get_next_line2(0, &(drawer->line), &(drawer->join));
		if (ret <= 0)
			return (ret = 0 ? print_input_error(4) : print_sys_error(errno));
		x = -1;
		while (drawer->line[++x] && x < drawer->last->piece_col)
		{
			if (drawer->line[x] != '.' && drawer->line[x] != '*')
				return (print_input_error(4));
			drawer->last->piece[y][x] = drawer->line[x];
		}
		if (x != drawer->last->piece_col)
			return (print_input_error(4));
		ft_strdel(&(drawer->line));
	}
	return (0);
}

int			check_piece(t_drawer *drawer, int same_map)
{
	int	ret;
	int	i;

	ret = 1;
	if (!same_map)
		ret = get_next_line2(0, &(drawer->line), &(drawer->join));
	if (ret <= 0)
		return (ret = 0 ? print_input_error(4) : print_sys_error(errno));
	if (ft_strncmp(drawer->line, "Piece ", 6))
		return (print_input_error(4));
	i = 6;
	if ((drawer->last->piece_row = get_num(drawer->line, &i)) <= 0\
		|| (drawer->last->piece_col = get_num(drawer->line, &i)) <= 0)
		return (print_input_error(4));
	ft_strdel(&(drawer->line));
	if (!(drawer->last->piece = create_piece(drawer)))
		return (print_sys_error(errno));
	if ((fill_piece(drawer)))
		return (1);
	return (0);
}
