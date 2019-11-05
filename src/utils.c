/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:56:27 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/24 18:59:56 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	get_num(char *line, int *i)
{
	int	nb;

	while (line[*i] && line[*i] == ' ')
		(*i)++;
	nb = ft_atoi(line + *i);
	while (line[*i] && line[*i] != ' ')
		(*i)++;
	return (nb);
}

int	star_in_row(char *row, int nb_col)
{
	int	i;

	i = -1;
	while (++i < nb_col)
		if (row[i] == '*')
			return (1);
	return (0);
}

int	star_in_col(char **piece, int index, int nb_row)
{
	int		i;

	i = -1;
	while (++i < nb_row)
		if (piece[i][index] == '*')
			return (1);
	return (0);
}
