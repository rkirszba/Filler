/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:51:47 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:13:41 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	bufferize_text(t_drawer *drawer, TTF_Font *police, char *str,
		SDL_Rect text_rect)
{
	static SDL_Color	color_fg = {255, 255, 255, 255};
	static SDL_Color	color_bg = {128, 33, 54, 50};
	SDL_Surface			*text_surface;
	SDL_Texture			*text_texture;

	text_surface = TTF_RenderText_Shaded(police, str, color_fg, color_bg);
	text_texture = SDL_CreateTextureFromSurface(drawer->renderer,\
			text_surface);
	SDL_FreeSurface(text_surface);
	SDL_RenderCopy(drawer->renderer, text_texture, NULL, &text_rect);
	SDL_DestroyTexture(text_texture);
}

void	print_header(t_drawer *drawer)
{
	SDL_Rect	text_rect;

	text_rect.y = HEADER_Y;
	TTF_SizeText(drawer->header_pol, "Welcome to Filler !", &(text_rect.w),\
				&(text_rect.h));
	text_rect.x = (NB_PIX_WDTH - text_rect.w) / 2;
	bufferize_text(drawer, drawer->header_pol, "Welcome to Filler !",\
		text_rect);
}

int		print_player_names(t_drawer *drawer, int player_nb)
{
	char		*trunc_name;
	SDL_Rect	text_rect;

	text_rect.y = PLAYER_Y;
	if (!(trunc_name = ft_strsub((player_nb == 1 ? drawer->player1\
			: drawer->player2), 0, 15)))
		return (print_sys_error(errno));
	TTF_SizeText(drawer->player_pol, trunc_name, &(text_rect.w),\
		&(text_rect.h));
	text_rect.x = (BEGIN_X - text_rect.w) / 2;
	if (player_nb == 1 && text_rect.x <= 0)
		text_rect.x = 15;
	if (player_nb == 2)
		text_rect.x += NB_PIX_WDTH - BEGIN_X;
	bufferize_text(drawer, drawer->player_pol, trunc_name, text_rect);
	free(trunc_name);
	return (0);
}

int		print_scores(t_drawer *drawer, int player_nb)
{
	char		*score;
	SDL_Rect	text_rect;

	text_rect.y = SCORE_Y;
	if (!(score = ft_itoa(player_nb == 1 ? drawer->current->p1_score\
				: drawer->current->p2_score)))
		return (1);
	TTF_SizeText(drawer->score_pol, score, &(text_rect.w),\
		&(text_rect.h));
	text_rect.x = (BEGIN_X - text_rect.w) / 2;
	if (player_nb == 2)
		text_rect.x += NB_PIX_WDTH - BEGIN_X;
	bufferize_text(drawer, drawer->score_pol, score, text_rect);
	free(score);
	return (0);
}
