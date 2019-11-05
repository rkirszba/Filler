/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 18:04:10 by rkirszba          #+#    #+#             */
/*   Updated: 2019/08/07 17:41:38 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	refresh_piece_data(t_filler *filler)
{
	free_piece(filler);
	filler->piece_row = 0;
	filler->piece_col = 0;
	filler->piece_xcut = 0;
	filler->piece_ycut = 0;
	filler->piece_xcut_end = 0;
	filler->piece_ycut_end = 0;
	filler->best_score = 0;
	filler->coor_x = 0;
	filler->coor_y = 0;
}

static int	player_nb_parser(t_filler *filler)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = get_next_line2(0, &line, &(filler->join));
	if (!ret || ret == -1)
		return (!ret ? 2 : print_sys_error(errno));
	if ((ret = ft_strncmp("$$$ exec p", line, 10)))
		print_input_error(9);
	if (!ret)
	{
		filler->player_nb = ft_atoi(line + 10);
		if (filler->player_nb != 1 && filler->player_nb != 2)
		{
			ret = 1;
			print_input_error(1);
		}
	}
	filler->state = 1;
	free(line);
	return (ret);
}

static void	check_fast_mode(t_filler *filler)
{
	int	i;
	int	j;
	int	player_score;
	int	opp_score;

	if (filler->fast_mode)
	{
		filler->fast_mode++;
		return ;
	}
	j = -1;
	player_score = 0;
	opp_score = 0;
	while ((i = -1) && ++j < filler->map_row)
		while (++i < filler->map_col)
		{
			if (filler->heat_map[j][i] == -(filler->player_nb))
				player_score++;
			else if (filler->heat_map[j][i] < 0)
				opp_score++;
		}
	if (opp_score == filler->opp_score && player_score > opp_score + 1)
		filler->fast_mode = 1;
	filler->opp_score = opp_score;
}

int			main(void)
{
	t_filler	filler;
	int			ret;

	ft_bzero(&filler, sizeof(t_filler));
	ret = 0;
	while (!ret)
	{
		refresh_piece_data(&filler);
		if (filler.state == 0)
			ret = player_nb_parser(&filler);
		if (!ret)
			ret = heat_map_filler(&filler);
		if (!ret)
			ret = piece_parser(&filler);
		check_fast_mode(&filler);
		if (!ret && filler.fast_mode < 2)
			piece_putter(&filler);
		else if (!ret)
			ft_printf("0 0\n");
	}
	free_struct_filler(&filler);
	return (ret == 1 ? 1 : 0);
}
