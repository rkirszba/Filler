/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 19:26:56 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:11:09 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	fill_rectangle(t_drawer *drawer, int x, int y, char c)
{
	SDL_Rect	rect;

	if (!(c == 'O' || c == 'o' || c == 'X' || c == 'x'))
		return ;
	rect.x = x;
	rect.y = y;
	rect.w = drawer->sq_size;
	rect.h = drawer->sq_size;
	if (c == 'O')
		SDL_SetRenderDrawColor(drawer->renderer, 60, 76, 250, 98);
	else if (c == 'o')
		SDL_SetRenderDrawColor(drawer->renderer, 48, 173, 253, 99);
	else if (c == 'X')
		SDL_SetRenderDrawColor(drawer->renderer, 38, 250, 59, 98);
	else
		SDL_SetRenderDrawColor(drawer->renderer, 156, 253, 25, 99);
	SDL_RenderFillRect(drawer->renderer, &rect);
}

static void	draw_grid(t_drawer *drawer)
{
	int			i;
	int			j;
	int			x;
	int			y;
	SDL_Rect	rect;

	SDL_SetRenderDrawColor(drawer->renderer, 255, 255, 255, 255);
	j = -1;
	y = drawer->begin_y;
	while (++j < drawer->nb_row)
	{
		i = -1;
		x = drawer->begin_x;
		while (++i < drawer->nb_col)
		{
			rect.x = x;
			rect.y = y;
			rect.w = drawer->sq_size;
			rect.h = drawer->sq_size;
			SDL_RenderDrawRect(drawer->renderer, &rect);
			x += drawer->sq_size;
		}
		y += drawer->sq_size;
	}
}

void		print_state(t_drawer *drawer)
{
	int	i;
	int	j;
	int	x;
	int	y;

	print_background(drawer);
	j = -1;
	y = drawer->begin_y;
	while (++j < drawer->nb_row)
	{
		i = -1;
		x = drawer->begin_x;
		while (++i < drawer->nb_col)
		{
			fill_rectangle(drawer, x, y, drawer->current->grid[j][i]);
			x += drawer->sq_size;
		}
		y += drawer->sq_size;
	}
	draw_grid(drawer);
	SDL_RenderPresent(drawer->renderer);
}
