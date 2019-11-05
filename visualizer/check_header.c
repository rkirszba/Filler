/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header_visu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 20:51:39 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 17:56:03 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static int	check_players(t_drawer *drawer, char *line, int player_nb)
{
	char	*start_name;
	char	*end_name;

	if (ft_strncmp(line, "$$$ exec p", 10))
		return (print_input_error(1));
	if (ft_atoi(line + 10) != player_nb)
		return (print_input_error(1));
	if (!(end_name = ft_strstr(line, ".filler]")))
		return (print_input_error(1));
	start_name = end_name - 1;
	if (*start_name == '/' || *start_name == '[')
		return (print_input_error(1));
	while (start_name > line + 10 && *start_name != '/'\
			&& *start_name != '[')
		start_name--;
	if (!(start_name > line + 10))
		return (print_input_error(1));
	if (player_nb == 1 && (!(drawer->player1 = ft_strsub(start_name,\
					1, end_name - start_name - 1))))
		return (print_sys_error(errno));
	if (player_nb == 2 && (!(drawer->player2 = ft_strsub(start_name,\
					1, end_name - start_name - 1))))
		return (print_sys_error(errno));
	return (0);
}

int			check_header(t_drawer *drawer)
{
	int		ret;
	char	*line;
	int		i;

	line = NULL;
	i = -1;
	while (++i < 9)
	{
		if ((ret = get_next_line2(0, &line, &(drawer->join))) <= 0)
		{
			free(line);
			return (ret == -1 ? print_sys_error(errno)\
				: print_input_error(1));
		}
		if (i == 6 || i == 8)
			if (check_players(drawer, line, i == 6 ? 1 : 2))
			{
				free(line);
				return (1);
			}
		free(line);
	}
	if (i != 9)
		return (print_input_error(1));
	return (0);
}
