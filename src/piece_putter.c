/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_putter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 15:37:59 by rkirszba          #+#    #+#             */
/*   Updated: 2019/08/07 17:03:37 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	actualize_coor(t_filler *filler, int score, int x, int y)
{
	filler->best_score = score;
	filler->coor_x = x - filler->piece_xcut;
	filler->coor_y = y - filler->piece_ycut;
}

static void	piece_checker(t_filler *filler, int x, int y)
{
	int	i;
	int	j;
	int	cover;
	int	score;

	cover = 0;
	score = 0;
	j = -1;
	while (++j + filler->piece_ycut < filler->piece_ycut_end && (i = -1))
		while (++i + filler->piece_xcut < filler->piece_xcut_end)
			if ((filler->piece)[j + filler->piece_ycut]\
				[i + filler->piece_xcut] == '*')
			{
				if ((filler->heat_map)[y + j][x + i] == -(filler->player_nb))
					cover++;
				else if ((filler->heat_map)[y + j][x + i] >= 0)
					score += (filler->heat_map)[y + j][x + i];
				else
					return ;
			}
	if (cover == 1 && (!filler->best_score || (filler->best_score && score\
				&& score < filler->best_score)))
		actualize_coor(filler, score, x, y);
}

void		piece_putter(t_filler *filler)
{
	int	piece_weidth;
	int	piece_height;
	int	x;
	int	y;

	if ((piece_weidth = filler->piece_xcut_end - filler->piece_xcut) > 0\
		&& (piece_height = filler->piece_ycut_end - filler->piece_ycut)\
				> 0)
	{
		y = -1;
		while (++y < filler->map_row - piece_height + 1)
		{
			x = -1;
			while (++x < filler->map_col - piece_weidth + 1)
				piece_checker(filler, x, y);
		}
	}
	ft_printf("%d %d\n", filler->coor_y, filler->coor_x);
}
