/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 21:53:07 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:10:38 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	free_map(t_drawer *drawer)
{
	t_map	*tmp;
	int		i;

	while (drawer->map)
	{
		tmp = drawer->map;
		drawer->map = drawer->map->next;
		i = -1;
		while (++i < drawer->nb_row)
			free(tmp->grid[i]);
		free(tmp->grid);
		i = -1;
		while (++i < tmp->piece_row)
			free(tmp->piece[i]);
		free(tmp->piece);
		free(tmp);
	}
}

void		free_manager(t_drawer *drawer)
{
	free(drawer->join);
	free(drawer->line);
	free(drawer->player1);
	free(drawer->player2);
	free_map(drawer);
	TTF_CloseFont(drawer->header_pol);
	TTF_CloseFont(drawer->player_pol);
	TTF_CloseFont(drawer->option_pol);
	SDL_DestroyRenderer(drawer->renderer);
	SDL_DestroyWindow(drawer->window);
}
