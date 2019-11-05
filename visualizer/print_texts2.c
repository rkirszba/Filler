/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texts2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:07:42 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:13:20 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	print_options2(t_drawer *drawer, SDL_Rect rect)
{
	TTF_SizeText(drawer->option_pol, "up arrow = accelerate",\
			&(rect.w), &(rect.h));
	bufferize_text(drawer, drawer->option_pol, "up arrow = accelerate",\
		rect);
	rect.y += rect.h;
	TTF_SizeText(drawer->option_pol, "down arrow = decelerate",\
			&(rect.w), &(rect.h));
	bufferize_text(drawer, drawer->option_pol, "down arrow = decelerate",\
		rect);
}

void		print_options(t_drawer *drawer)
{
	SDL_Rect	rect;

	rect.x = OPTION_X;
	rect.y = NB_PIX_HGHT - BEGIN_Y / 2;
	TTF_SizeText(drawer->option_pol, "space = start / stop",\
			&(rect.w), &(rect.h));
	bufferize_text(drawer, drawer->option_pol, "space = start / stop", rect);
	rect.y += rect.h;
	TTF_SizeText(drawer->option_pol, "esc = quit", &(rect.w), &(rect.h));
	bufferize_text(drawer, drawer->option_pol, "esc = quit", rect);
	rect.y += rect.h;
	TTF_SizeText(drawer->option_pol, "right arrow = next move",\
			&(rect.w), &(rect.h));
	bufferize_text(drawer, drawer->option_pol, "right arrow = next move",\
		rect);
	rect.y += rect.h;
	TTF_SizeText(drawer->option_pol, "left arrow = previous move",\
			&(rect.w), &(rect.h));
	bufferize_text(drawer, drawer->option_pol, "left arrow = previous move",\
		rect);
	rect.y += rect.h;
	print_options2(drawer, rect);
}

static int	print_draw(t_drawer *drawer)
{
	SDL_Rect	text_rect;

	TTF_SizeText(drawer->header_pol, "That's a draw !", &(text_rect.w),\
			&(text_rect.h));
	text_rect.x = (NB_PIX_WDTH - text_rect.w) / 2;
	bufferize_text(drawer, drawer->header_pol, "That's a draw !", text_rect);
	return (0);
}

int			print_winner(t_drawer *drawer)
{
	char		*trunc_name;
	char		*str;
	SDL_Rect	text_rect;
	int			winner;

	if (drawer->p1_score == drawer->p2_score)
		return (print_draw(drawer));
	text_rect.y = WINNER_Y;
	winner = drawer->p1_score > drawer->p2_score ? 1 : 2;
	if (!(trunc_name = ft_strsub((winner == 1 ? drawer->player1
					: drawer->player2), 0, 15))\
			|| !(str = ft_strjoin(trunc_name, (winner == 1 ? "(p1) won !"
					: "(p2) won !"))))
	{
		free(trunc_name);
		return (print_sys_error(errno));
	}
	TTF_SizeText(drawer->header_pol, str, &(text_rect.w), &(text_rect.h));
	text_rect.x = (NB_PIX_WDTH - text_rect.w) / 2;
	bufferize_text(drawer, drawer->header_pol, str, text_rect);
	free(trunc_name);
	free(str);
	return (0);
}
