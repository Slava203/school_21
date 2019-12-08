/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:35:22 by daron             #+#    #+#             */
/*   Updated: 2019/11/22 14:34:09 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

SDL_Rect change_rect(int x, int y, int w, int h)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

char *create_string_coord(t_sdl *sdl, char *name)
{
	char *ptr;

	ptr = ft_strjoin_del(name, " ", 'N');
	ptr = ft_strjoin_del(ptr, ft_itoa(sdl->cam.pos.x), 'B');
	ptr = ft_strjoin_del(ptr, " ", 'L');
	ptr = ft_strjoin_del(ptr, ft_itoa(sdl->cam.pos.y), 'B');
	ptr = ft_strjoin_del(ptr, " ", 'L');
	ptr = ft_strjoin_del(ptr, ft_itoa(sdl->cam.pos.z), 'B');
	return (ptr);
}

void print_text(t_sdl *sdl)
{
	SDL_Rect Message_rect;
	int height;
	int delta;
	char *str;
	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;

	height = 15;
	delta = 18;
	TTF_Font* Sans = TTF_OpenFont("open-sans/OpenSans-Light.ttf", 15);
	SDL_Color White = { 255, 255, 255, 0 };

	str = create_string_coord(sdl, "cam_pos");
	printf("%s\n", str);
	surfaceMessage = TTF_RenderText_Solid(Sans, "cam_position", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	Message = SDL_CreateTextureFromSurface(sdl->render, surfaceMessage); //now you can convert it into a texture

	//Message_rect = change_rect(W_WIDTH - 140 , height, 120, 25);
	Message_rect = change_rect(W_WIDTH - 140 , height, 25, 25);
	SDL_RenderCopy(sdl->render, Message, NULL, &Message_rect);

	/*height += delta;
	Message_rect = change_rect(W_WIDTH - 120 , height, 100, 25);
	SDL_RenderCopy(sdl->render, Message, NULL, &Message_rect);

	height += delta;
	Message_rect = change_rect(W_WIDTH - 120 , height, 100, 25);
	SDL_RenderCopy(sdl->render, Message, NULL, &Message_rect);

	height += delta;
	Message_rect = change_rect(W_WIDTH - 120 , height, 100, 25);
	SDL_RenderCopy(sdl->render, Message, NULL, &Message_rect);

	height += delta;
	Message_rect = change_rect(W_WIDTH - 120 , height, 100, 25);
	SDL_RenderCopy(sdl->render, Message, NULL, &Message_rect);


	height += 30;
	Message_rect = change_rect(W_WIDTH - 120 , height, 100, 25);
	SDL_RenderCopy(sdl->render, Message, NULL, &Message_rect);

	height += delta;
	Message_rect = change_rect(W_WIDTH - 120 , height, 100, 25);
	SDL_RenderCopy(sdl->render, Message, NULL, &Message_rect);

	height += delta;
	Message_rect = change_rect(W_WIDTH - 120 , height, 100, 25);
	SDL_RenderCopy(sdl->render, Message, NULL, &Message_rect);

	height += delta;
	Message_rect = change_rect(W_WIDTH - 120 , height, 100, 25);
	SDL_RenderCopy(sdl->render, Message, NULL, &Message_rect);*/
}