/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_background.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:31:07 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:13:40 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	fill_rectangle(t_drawer *drawer, int x, int y, char c)
{
	SDL_Rect	rect;

	if (drawer->current->player == 1)
		SDL_SetRenderDrawColor(drawer->renderer, 60, 76, 250, 98);
	else
		SDL_SetRenderDrawColor(drawer->renderer, 38, 250, 59, 98);
	if (c != '*')
		return ;
	rect.x = x;
	rect.y = y;
	rect.w = drawer->current->piece_sq_size;
	rect.h = drawer->current->piece_sq_size;
	SDL_RenderFillRect(drawer->renderer, &rect);
}

static void	draw_rectangle(t_drawer *drawer, int x, int y, int c)
{
	SDL_Rect	rect;

	SDL_SetRenderDrawColor(drawer->renderer, 255, 255, 255, 255);
	if (c != '*')
		return ;
	rect.x = x;
	rect.y = y;
	rect.w = drawer->current->piece_sq_size;
	rect.h = drawer->current->piece_sq_size;
	SDL_RenderDrawRect(drawer->renderer, &rect);
}

static void	compute_piece_pos(t_drawer *drawer)
{
	drawer->current->piece_sq_size = (BEGIN_X - (2 * PIECE_X))\
				/ drawer->current->piece_col;
	if (drawer->current->piece_sq_size > MAX_PIECE_SQ_SIZE)
		drawer->current->piece_sq_size = MAX_PIECE_SQ_SIZE;
	drawer->current->piece_begin_x = (BEGIN_X -\
				drawer->current->piece_sq_size\
				* drawer->current->piece_col)\
			/ 2;
	if (drawer->current->player == 2)
		drawer->current->piece_begin_x += NB_PIX_WDTH - BEGIN_X;
	drawer->current->piece_begin_y = PIECE_Y;
}

static void	show_piece(t_drawer *drawer)
{
	int	i;
	int	j;
	int	x;
	int	y;

	if (!drawer->current->piece || drawer->current->piece_row > MAX_PIECE_ROW\
		|| drawer->current->piece_col > MAX_PIECE_COL)
		return ;
	compute_piece_pos(drawer);
	j = -1;
	y = drawer->current->piece_begin_y;
	while (++j < drawer->current->piece_row)
	{
		i = -1;
		x = drawer->current->piece_begin_x;
		while (++i < drawer->current->piece_col)
		{
			fill_rectangle(drawer, x, y, drawer->current->piece[j][i]);
			draw_rectangle(drawer, x, y, drawer->current->piece[j][i]);
			x += drawer->current->piece_sq_size;
		}
		y += drawer->current->piece_sq_size;
	}
}

int			print_background(t_drawer *drawer)
{
	SDL_SetRenderDrawColor(drawer->renderer, 128, 33, 54, 50);
	SDL_RenderClear(drawer->renderer);
	print_header(drawer);
	print_options(drawer);
	if (print_player_names(drawer, 1) || print_player_names(drawer, 2))
		return (1);
	if (print_scores(drawer, 1) || print_scores(drawer, 2))
		return (1);
	if (drawer->current->last && print_winner(drawer))
		return (1);
	show_piece(drawer);
	return (0);
}
