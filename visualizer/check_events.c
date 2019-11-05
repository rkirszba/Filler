/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:21:28 by rkirszba          #+#    #+#             */
/*   Updated: 2019/07/25 18:10:02 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static int	handle_key_events2(t_drawer *drawer, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
	{
		if (drawer->delay < 2000)
			drawer->delay += (drawer->delay * 20) / 100;
	}
	else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
	{
		if (drawer->follow)
			drawer->follow = 0;
		else
			drawer->follow = 1;
	}
	return (0);
}

static int	handle_key_events(t_drawer *drawer, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		return (1);
	else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
	{
		if (drawer->current->prev)
			drawer->current = drawer->current->prev;
		print_state(drawer);
		drawer->follow = 0;
	}
	else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
	{
		if (drawer->current->next)
			drawer->current = drawer->current->next;
		print_state(drawer);
		drawer->follow = 0;
	}
	else if (event.key.keysym.scancode == SDL_SCANCODE_UP)
	{
		if (drawer->delay > 20)
			drawer->delay -= (drawer->delay * 20) / 100;
	}
	else
		return (handle_key_events2(drawer, event));
	return (0);
}

int			check_events(t_drawer *drawer)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				return (1);
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (handle_key_events(drawer, event))
				return (1);
		}
	}
	return (0);
}
