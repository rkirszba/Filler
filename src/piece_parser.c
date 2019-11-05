/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:45:38 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/24 19:22:05 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	generate_piece(t_filler *filler)
{
	int	i;

	if (!(filler->piece = (char**)malloc(sizeof(char*) * filler->piece_row)))
		return (print_sys_error(errno));
	ft_bzero(filler->piece, sizeof(char*) * filler->piece_row);
	i = -1;
	while (++i < filler->piece_row)
		if (!(filler->piece[i] =\
				(char*)malloc(sizeof(char) * filler->piece_col)))
		{
			free_piece(filler);
			return (print_sys_error(errno));
		}
	return (0);
}

static int	fill_line(t_filler *filler, char *line, int y)
{
	int	x;

	x = -1;
	while (line[++x] && x < filler->piece_col)
	{
		if (line[x] != '.' && line[x] != '*')
			return (print_input_error(!line[x] ? 4 : 8));
		(filler->piece)[y][x] = line[x];
	}
	if (x != filler->piece_col)
		return (print_input_error(4));
	return (0);
}

static int	piece_filler(t_filler *filler)
{
	char	*line;
	int		ret;
	int		y;

	y = -1;
	while (++y < filler->piece_row\
		&& (ret = get_next_line2(0, &line, &(filler->join))))
	{
		if (ret == -1)
			return (print_sys_error(errno));
		if (fill_line(filler, line, y))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (y != filler->piece_row ? print_input_error(5) : 0);
}

static void	piece_cutter(t_filler *filler)
{
	int	i;

	i = -1;
	while (++i < filler->piece_row)
		if (star_in_row((filler->piece)[i], filler->piece_col))
			break ;
	filler->piece_ycut = i;
	i = filler->piece_row;
	while (--i >= 0)
		if (star_in_row((filler->piece)[i], filler->piece_col))
			break ;
	filler->piece_ycut_end = i + 1;
	i = -1;
	while (++i < filler->piece_col)
		if (star_in_col(filler->piece, i, filler->piece_row))
			break ;
	filler->piece_xcut = i;
	i = filler->piece_col;
	while (--i >= 0)
		if (star_in_col(filler->piece, i, filler->piece_row))
			break ;
	filler->piece_xcut_end = i + 1;
}

int			piece_parser(t_filler *filler)
{
	char	*line;
	int		ret;
	int		i;

	if (get_next_line2(0, &line, &(filler->join)) == -1)
		return (print_sys_error(errno));
	if ((ret = ft_strncmp("Piece ", line, 6)))
		print_input_error(7);
	i = 6;
	if (!ret && ((filler->piece_row = get_num(line, &i)) <= 0\
			|| (filler->piece_col = get_num(line, &i)) <= 0))
	{
		ret = 1;
		print_input_error(2);
	}
	if (!ret)
		ret = generate_piece(filler);
	if (!ret)
		ret = piece_filler(filler);
	if (!ret)
		piece_cutter(filler);
	free(line);
	return (ret);
}
