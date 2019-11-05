/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:52:28 by rkirszba          #+#    #+#             */
/*   Updated: 2019/08/07 17:03:36 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <sys/types.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"

typedef struct	s_queue
{
	int				x;
	int				y;
	struct s_queue	*next;
}				t_queue;

typedef struct	s_filler
{
	char	*join;
	int		state;
	int		player_nb;
	int		map_row;
	int		map_col;
	int		**heat_map;
	t_queue	*queue;
	char	**piece;
	int		piece_row;
	int		piece_col;
	int		piece_xcut;
	int		piece_ycut;
	int		piece_xcut_end;
	int		piece_ycut_end;
	int		best_score;
	int		coor_x;
	int		coor_y;
	int		opp_score;
	int		fast_mode;
}				t_filler;

/*
**  heat map generator
*/

int				heat_map_filler(t_filler *filler);
int				map_reader(t_filler *filler);

/*
** piece parser
*/

int				piece_parser(t_filler *filler);

/*
** piece putter
*/

void			piece_putter(t_filler *filler);

/*
** utils
*/

int				get_num(char *line, int *i);
int				star_in_col(char **piece, int index, int nb_row);
int				star_in_row(char *row, int nb_col);

/*
** errors
*/

int				print_sys_error(int errnum);
int				print_input_error(int errnum);

/*
** free manager
*/

void			free_struct_filler(t_filler *filler);
void			free_queue(t_queue **queue);
void			free_heat_map(t_filler *filler);
void			free_piece(t_filler *filler);

#endif
