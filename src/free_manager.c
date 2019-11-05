/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:49:13 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/24 17:40:50 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_piece(t_filler *filler)
{
	int	i;

	i = -1;
	while (++i < filler->piece_row)
	{
		free((filler->piece)[i]);
		filler->piece[i] = NULL;
	}
	free(filler->piece);
	filler->piece = NULL;
}

void	free_heat_map(t_filler *filler)
{
	int	i;

	i = -1;
	while (++i < filler->map_row)
	{
		free((filler->heat_map)[i]);
		(filler->heat_map)[i] = NULL;
	}
	free(filler->heat_map);
	filler->heat_map = NULL;
}

void	free_queue(t_queue **queue)
{
	t_queue	*current;
	t_queue	*tmp;

	if (!(*queue))
		return ;
	current = *queue;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*queue = NULL;
}

void	free_struct_filler(t_filler *filler)
{
	if (filler->queue)
		free_queue(&(filler->queue));
	if (filler->heat_map)
		free_heat_map(filler);
	if (filler->piece)
		free_piece(filler);
	if (filler->join)
		free(filler->join);
}
