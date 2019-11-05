/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:47:18 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:13:42 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static int	init_drawer(t_drawer *drawer)
{
	if (!(drawer->window = SDL_CreateWindow("Filler", SDL_WINDOWPOS_UNDEFINED,\
			SDL_WINDOWPOS_UNDEFINED, NB_PIX_HGHT, NB_PIX_WDTH,\
			SDL_WINDOW_FULLSCREEN_DESKTOP)))
		return (print_sdl_error(2));
	if (!(drawer->renderer = SDL_CreateRenderer(drawer->window, -1,\
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		return (print_sdl_error(3));
	if (!(drawer->header_pol = TTF_OpenFont("./SuperMario256.ttf",\
				HEADER_POL_SIZE))\
		|| !(drawer->player_pol = TTF_OpenFont("./SuperMario256.ttf",\
				PLAYER_POL_SIZE))\
		|| !(drawer->option_pol = TTF_OpenFont("./SuperMario256.ttf",\
				OPTION_POL_SIZE))
		|| !(drawer->score_pol = TTF_OpenFont("./SuperMario256.ttf",\
				SCORE_POL_SIZE)))
		return (print_sdl_error(4));
	drawer->delay = 100;
	drawer->follow = 1;
	return (0);
}

static int	compute_position(t_drawer *drawer)
{
	int	min_sq_size;
	int	tmp;

	if (drawer->nb_col > MAX_COL || drawer->nb_row > MAX_ROW)
		return (print_input_error(6));
	min_sq_size = MAP_SIZE_X / drawer->nb_col;
	tmp = MAP_SIZE_Y / drawer->nb_row;
	if (tmp < min_sq_size)
		min_sq_size = tmp;
	if (min_sq_size > MAX_SQUARE_SIZE)
		min_sq_size = MAX_SQUARE_SIZE;
	drawer->sq_size = min_sq_size;
	drawer->begin_x = (NB_PIX_WDTH - (drawer->sq_size * drawer->nb_col)) / 2;
	drawer->begin_y = (NB_PIX_HGHT - (drawer->sq_size * drawer->nb_row)) / 2;
	return (0);
}

static int	visualize(t_drawer *drawer)
{
	if ((check_input(drawer)))
		return (1);
	if ((compute_position(drawer)))
		return (1);
	print_state(drawer);
	drawer->follow = 0;
	while (42)
	{
		if (!drawer->end && (check_input(drawer)))
			return (1);
		if (check_events(drawer))
			return (0);
		if (drawer->follow)
			print_state(drawer);
		if (drawer->follow && drawer->current->next)
			drawer->current = drawer->current->next;
		if (drawer->follow)
			SDL_Delay(drawer->delay);
	}
	return (0);
}

int			main(void)
{
	t_drawer	drawer;
	int			ret;

	if ((SDL_Init(SDL_INIT_VIDEO)))
		return (print_sdl_error(1));
	if ((TTF_Init()))
		return (print_sdl_error(5));
	ft_bzero(&drawer, sizeof(t_drawer));
	ret = check_header(&drawer);
	if (ret == 0)
		ret = init_drawer(&drawer);
	if (ret == 0)
		ret = visualize(&drawer);
	free_manager(&drawer);
	TTF_Quit();
	SDL_Quit();
	return (0);
}
