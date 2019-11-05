/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_nb_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:13:49 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/24 18:24:02 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		player_nb_parser(t_filler *filler)
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
