/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:30:37 by daron             #+#    #+#             */
/*   Updated: 2019/11/19 16:47:56 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	events(t_sdl *sdl)
{
	SDL_Event		event;

	while(1)
		while (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
		{
			if ((SDL_QUIT == sdl->event.type) || (SDL_SCANCODE_ESCAPE == sdl->event.key.keysym.scancode))
				exit(0);
			/*else if (SDLK_w == sdl->event.key.keysym.sym || SDLK_s == sdl->event.key.keysym.sym || SDLK_a == sdl->event.key.keysym.sym ||
					SDLK_d == sdl->event.key.keysym.sym || SDLK_KP_PLUS == sdl->event.key.keysym.sym || SDLK_KP_MINUS == sdl->event.key.keysym.sym)
				move_key(sdl);
			else if (SDLK_LEFT == sdl->event.key.keysym.sym || SDLK_RIGHT == sdl->event.key.keysym.sym ||
					SDLK_DOWN == sdl->event.key.keysym.sym || SDLK_UP == sdl->event.key.keysym.sym)
				rotate_key(sdl);
			else if (SDLK_p == sdl->event.key.keysym.sym && sdl->dital < 16)
			{
				sdl->dital *= 2;
				ray_tracing_init(sdl);
			}
			else if (SDLK_o == sdl->event.key.keysym.sym && sdl->dital > 1)
			{
				sdl->dital /= 2;
				ray_tracing_init(sdl);
			}*/
			//-------------------------------------------------------------------------------
			else if (SDLK_g == event.key.keysym.sym && sdl->dital > 1)
			{
				sdl->gloss_activ = (sdl->gloss_activ == 0)? 1 : 0;
				ray_tracing_init(sdl);
			}
		}
}

void move_key(t_sdl *sdl)
{
	float delta = 10.0;

	if (SDLK_w == sdl->event.key.keysym.sym)
	{
		sdl->dital = 1;
		sdl->cam.rot = (t_vector){sdl->cam.rot.x + delta * sdl->j.x, sdl->cam.rot.y + delta * sdl->j.y, sdl->cam.rot.z + delta * sdl->j.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x + delta * sdl->j.x, sdl->cam.pos.y + delta * sdl->j.y, sdl->cam.pos.z - delta * sdl->j.z};
		ray_tracing_init(sdl);
	}
	else if (SDLK_s == sdl->event.key.keysym.sym)
	{
		sdl->dital = 1;
		sdl->cam.rot = (t_vector){sdl->cam.rot.x - delta * sdl->j.x, sdl->cam.rot.y - delta * sdl->j.y, sdl->cam.rot.z - delta * sdl->j.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x - delta * sdl->j.x, sdl->cam.pos.y - delta * sdl->j.y, sdl->cam.pos.z - delta * sdl->j.z};
		ray_tracing_init(sdl);
	}
	else if (SDLK_a == sdl->event.key.keysym.sym)
	{
		sdl->dital = 1;
		sdl->cam.rot = (t_vector){sdl->cam.rot.x + delta * sdl->i.x, sdl->cam.rot.y + delta * sdl->i.y, sdl->cam.rot.z + delta * sdl->i.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x + delta * sdl->i.x, sdl->cam.pos.y + delta * sdl->i.y, sdl->cam.pos.z + delta * sdl->i.z};
		ray_tracing_init(sdl);
	}
	else if (SDLK_d == sdl->event.key.keysym.sym)
	{
		sdl->dital = 1;
		sdl->cam.rot = (t_vector){sdl->cam.rot.x - delta * sdl->i.x, sdl->cam.rot.y - delta * sdl->i.y, sdl->cam.rot.z - delta * sdl->i.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x - delta * sdl->i.x, sdl->cam.pos.y - delta * sdl->i.y, sdl->cam.pos.z - delta * sdl->i.z};
		ray_tracing_init(sdl);
	}
	else if (SDLK_KP_PLUS == sdl->event.key.keysym.sym)
	{
		sdl->dital = 1;
		sdl->cam.rot = (t_vector){sdl->cam.rot.x + delta * sdl->k.x, sdl->cam.rot.y + delta * sdl->k.y, sdl->cam.rot.z + delta * sdl->k.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x + delta * sdl->k.x, sdl->cam.pos.y + delta * sdl->k.y, sdl->cam.pos.z + delta * sdl->k.z};
		ray_tracing_init(sdl);
	}
	else if (SDLK_KP_MINUS == sdl->event.key.keysym.sym)
	{
		sdl->dital = 1;
		sdl->cam.rot = (t_vector){sdl->cam.rot.x - delta * sdl->k.x, sdl->cam.rot.y - delta * sdl->k.y, sdl->cam.rot.z - delta * sdl->k.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x - delta * sdl->k.x, sdl->cam.pos.y - delta * sdl->k.y, sdl->cam.pos.z - delta * sdl->k.z};
		ray_tracing_init(sdl);
	}
}

void rotate_key(t_sdl *sdl)
{
	float alpha = 0.05;
	float tmp;

	if (SDLK_LEFT == sdl->event.key.keysym.sym && (tmp = sdl->cam.pos.x) < 20000)
	{
		sdl->dital = 1;
		sdl->cam.pos.x = sdl->cam.pos.x * cosf(alpha) + sdl->cam.pos.z * sinf(alpha);
		sdl->cam.pos.z = tmp * (-sinf(alpha)) + sdl->cam.pos.z * cosf(alpha);
		ray_tracing_init(sdl);
	}
	else if (SDLK_RIGHT == sdl->event.key.keysym.sym && (tmp = sdl->cam.pos.x) > -20000)
	{
		sdl->dital = 1;
		sdl->cam.pos.x = sdl->cam.pos.x * cosf(-alpha) + sdl->cam.pos.z * sinf(-alpha);
		sdl->cam.pos.z = tmp * (-sinf(-alpha)) + sdl->cam.pos.z * cosf(-alpha);
		ray_tracing_init(sdl);
	}
	else if (SDLK_DOWN == sdl->event.key.keysym.sym && (tmp = sdl->cam.pos.y) > -20000)
	{
		sdl->dital = 1;
		sdl->cam.pos.y = sdl->cam.pos.y * cosf(-alpha) + sdl->cam.pos.z * (-sinf(-alpha));
		sdl->cam.pos.z = tmp * sinf(-alpha) + sdl->cam.pos.z * cosf(-alpha);
		ray_tracing_init(sdl);
	}
	else if (SDLK_UP == sdl->event.key.keysym.sym && (tmp = sdl->cam.pos.y) < 20000)
	{
		sdl->dital = 1;
		sdl->cam.pos.y = sdl->cam.pos.y * cosf(alpha) + sdl->cam.pos.z * (-sinf(alpha));
		sdl->cam.pos.z = tmp * sinf(alpha) + sdl->cam.pos.z * cosf(alpha);
		ray_tracing_init(sdl);
	}
}