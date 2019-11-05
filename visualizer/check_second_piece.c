/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_second_piece.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:45:00 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:08:48 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	copy_grid(t_drawer *drawer, char **dest, char **src)
{
	int x;
	int y;

	y = -1;
	while (++y < drawer->nb_row)
	{
		x = -1;
		while (++x < drawer->nb_col)
			dest[y][x] = src[y][x];
	}
}

int			check_second_piece(t_drawer *drawer)
{
	int	ret;

	ret = get_next_line2(0, &(drawer->line), &(drawer->join));
	if (ret <= 0)
		return (ret = 0 ? print_input_error(5) : print_sys_error(errno));
	if (ft_strncmp(drawer->line, "Piece ", 6))
		return (0);
	print_state(drawer);
	if (map_manager(drawer, 1))
		return (1);
	copy_grid(drawer, drawer->last->grid, drawer->last->prev->grid);
	drawer->last->p1_score = drawer->last->prev->p1_score;
	drawer->last->p2_score = drawer->last->prev->p2_score;
	if (check_piece(drawer, 1))
		return (1);
	return (2);
}
