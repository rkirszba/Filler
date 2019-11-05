/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:51:14 by rkirszba          #+#    #+#             */
/*   Updated: 2019/08/07 16:01:49 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <SDL.h>
# include <SDL_ttf.h>
# include <errno.h>
# include "libft.h"

# define NB_PIX_WDTH 2560
# define NB_PIX_HGHT 1440
# define MAP_SIZE_X 1600
# define MAP_SIZE_Y 800
# define BEGIN_X 480
# define BEGIN_Y 320
# define MAX_NAME_LEN 15
# define MAX_COL 150
# define MAX_ROW 100
# define MAX_SQUARE_SIZE 100
# define HEADER_POL_SIZE 80
# define PLAYER_POL_SIZE 40
# define OPTION_POL_SIZE 25
# define SCORE_POL_SIZE 36
# define MAX_DELAY 5000
# define PIECE_X 15
# define PIECE_Y 500
# define MAX_PIECE_SQ_SIZE 50
# define MAX_PIECE_ROW 30
# define MAX_PIECE_COL 30
# define HEADER_Y 40
# define PLAYER_Y 290
# define SCORE_Y 420
# define WINNER_Y 1200
# define OPTION_X 15

typedef struct	s_map
{
	char			**grid;
	char			**piece;
	int				piece_row;
	int				piece_col;
	int				piece_sq_size;
	int				piece_begin_x;
	int				piece_begin_y;
	int				player;
	int				p1_score;
	int				p2_score;
	int				last;
	struct s_map	*prev;
	struct s_map	*next;
}				t_map;

typedef struct	s_drawer
{
	char			*join;
	char			*line;
	int				begin_x;
	int				begin_y;
	int				nb_row;
	int				nb_col;
	int				sq_size;
	int				delay;
	int				follow;
	int				end;
	char			*player1;
	char			*player2;
	int				p1_score;
	int				p2_score;
	int				state;
	t_map			*map;
	t_map			*current;
	t_map			*last;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*header_pol;
	TTF_Font		*player_pol;
	TTF_Font		*score_pol;
	TTF_Font		*option_pol;
}				t_drawer;

/*
** parsing functions
*/

int				check_header(t_drawer *drawer);
int				check_input(t_drawer *drawer);
int				map_manager(t_drawer *drawer, int same_map);
int				check_piece(t_drawer *drawer, int same_map);
int				check_second_piece(t_drawer *drawer);

/*
** visualizing functions
*/

void			print_state(t_drawer *drawer);
int				print_background(t_drawer *drawer);
void			print_header(t_drawer *drawer);
int				print_player_names(t_drawer *drawer, int player_nb);
int				print_scores(t_drawer *drawer, int player_nb);
int				print_winner(t_drawer *drawer);
void			print_options(t_drawer *drawer);
void			bufferize_text(t_drawer *drawer, TTF_Font *police, char *str,
				SDL_Rect text_rect);

/*
** errors functions
*/

int				print_sys_error(int errnum);
int				print_sdl_error(int errnum);
int				print_input_error(int errnum);

/*
** events functions
*/

int				check_events(t_drawer *drawer);

/*
** utils functions
*/

int				get_num(char *line, int *i);

/*
** free_manager
*/

void			free_manager(t_drawer *drawer);

#endif
