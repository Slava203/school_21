/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:30:37 by daron             #+#    #+#             */
/*   Updated: 2019/11/20 14:40:51 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	events(t_sdl *sdl)
{
	while(1)
		while (SDL_PollEvent(&sdl->event))
		{
			if ((SDL_QUIT == sdl->event.type) || (SDL_SCANCODE_ESCAPE == sdl->event.key.keysym.scancode))
			{
				my_free(sdl);
				exit(0);
			}
			else if (SDLK_RETURN == sdl->event.key.keysym.sym)
				sdl->select_obj = NULL;
			else if (sdl->event.type == SDL_KEYDOWN && sdl->select_obj == NULL)
				key_down(sdl);
			else if (sdl->event.type == SDL_KEYDOWN && sdl->select_obj != NULL)
				key_down_for_object(sdl);
			else if (sdl->event.type == SDL_MOUSEBUTTONDOWN)
				mouse_down(sdl);
		}
}
//------------------------------------------------------------------------------
static t_object *mouse_intersection(double u, double v, t_vector *pos, t_sdl *sdl)
{
	t_object *obj;

	sdl->k = vec_sub(&sdl->cam.rot, pos);
	sdl->k = vec_norm(&sdl->k);

	sdl->i = vec_cross(&sdl->k, &(t_vector){0.0, 1.0, 0.0});
	sdl->i = vec_norm(&sdl->i);

	sdl->j = vec_cross(&sdl->i, &sdl->k);

	sdl->ray_dir = (t_vector){u * sdl->i.x + v * sdl->j.x + FOV * sdl->k.x,
						   u * sdl->i.y + v * sdl->j.y + FOV * sdl->k.y,
						   u * sdl->i.z + v * sdl->j.z + FOV * sdl->k.z};
	sdl->ray_dir = vec_norm(&sdl->ray_dir);

	obj = intersection(sdl, &sdl->ray_dir, pos);
	return (obj);

}

void mouse_down(t_sdl *sdl)
{
	int x;
	int y;
	double	u;
	double	v;
	t_vector pos;

	if (SDL_BUTTON_LEFT == sdl->event.button.button)
	{
		SDL_GetMouseState(&x, &y);
		u = (W_WIDTH - (double)x * 2.0) / W_HEIGHT;
		v = (W_HEIGHT - (double)y * 2.0) / W_WIDTH;
		pos = (t_vector){sdl->cam.pos.x + u, sdl->cam.pos.y + v, sdl->cam.pos.z};
		sdl->select_obj = mouse_intersection(u, v, &pos, sdl);
		//printf("name = %d\n", sdl->select_obj->name);
	}
}
//------------------------------------------------------------------------------

void key_down_for_object(t_sdl *sdl)
{
	//printf("key_down_for_object\n");
	if (SDLK_KP_1 == sdl->event.key.keysym.sym || SDLK_KP_2 == sdl->event.key.keysym.sym)
		resize_object(sdl);
	else if (SDLK_w == sdl->event.key.keysym.sym || SDLK_s == sdl->event.key.keysym.sym ||
			 SDLK_a == sdl->event.key.keysym.sym || SDLK_d == sdl->event.key.keysym.sym ||
			SDLK_KP_PLUS == sdl->event.key.keysym.sym || SDLK_KP_MINUS == sdl->event.key.keysym.sym)
		move_object(sdl);

}

void move_object(t_sdl *sdl)
{
	float delta = 10.0;

	sdl->dital = 1;
	if (SDLK_w == sdl->event.key.keysym.sym)
		sdl->select_obj->pos = (t_vector){sdl->select_obj->pos.x + delta * sdl->j.x, sdl->select_obj->pos.y + delta * sdl->j.y, sdl->select_obj->pos.z + delta * sdl->j.z};
	else if (SDLK_s == sdl->event.key.keysym.sym)
		sdl->select_obj->pos = (t_vector){sdl->select_obj->pos.x - delta * sdl->j.x, sdl->select_obj->pos.y - delta * sdl->j.y, sdl->select_obj->pos.z - delta * sdl->j.z};
	else if (SDLK_a == sdl->event.key.keysym.sym)
		sdl->select_obj->pos = (t_vector){sdl->select_obj->pos.x + delta * sdl->i.x, sdl->select_obj->pos.y + delta * sdl->i.y, sdl->select_obj->pos.z + delta * sdl->i.z};
	else if (SDLK_d == sdl->event.key.keysym.sym)
		sdl->select_obj->pos = (t_vector){sdl->select_obj->pos.x - delta * sdl->i.x, sdl->select_obj->pos.y - delta * sdl->i.y, sdl->select_obj->pos.z - delta * sdl->i.z};
	else if (SDLK_KP_PLUS == sdl->event.key.keysym.sym)
		sdl->select_obj->pos = (t_vector){sdl->select_obj->pos.x + delta * sdl->k.x, sdl->select_obj->pos.y + delta * sdl->k.y, sdl->select_obj->pos.z + delta * sdl->k.z};
	else if (SDLK_KP_MINUS == sdl->event.key.keysym.sym)
		sdl->select_obj->pos = (t_vector){sdl->select_obj->pos.x - delta * sdl->k.x, sdl->select_obj->pos.y - delta * sdl->k.y, sdl->select_obj->pos.z - delta * sdl->k.z};
	ray_tracing_init(sdl);
}

void resize_object(t_sdl *sdl)
{
	float delt = 0.5;

	if (sdl->select_obj->name != PLANE_ID)
	{
		if (SDLK_KP_1 == sdl->event.key.keysym.sym && sdl->select_obj->r > 0.5)
			sdl->select_obj->r -= delt;
		else if (SDLK_KP_2 == sdl->event.key.keysym.sym && sdl->select_obj->r < 200.0)
			sdl->select_obj->r += delt;
	}
	//printf("resize_object %g\n", sdl->select_obj->r);
	ray_tracing_init(sdl);
}

//------------------------------------------------------------------------------
void key_down(t_sdl *sdl)
{

	if (SDLK_w == sdl->event.key.keysym.sym || SDLK_s == sdl->event.key.keysym.sym ||
			 SDLK_a == sdl->event.key.keysym.sym || SDLK_d == sdl->event.key.keysym.sym ||
			 SDLK_KP_PLUS == sdl->event.key.keysym.sym ||
			 SDLK_KP_MINUS == sdl->event.key.keysym.sym)
		move_key(sdl);
	else if (SDLK_LEFT == sdl->event.key.keysym.sym || SDLK_RIGHT == sdl->event.key.keysym.sym ||
			 SDLK_DOWN == sdl->event.key.keysym.sym || SDLK_UP == sdl->event.key.keysym.sym)
		rotate_key(sdl);
	else if (SDLK_p == sdl->event.key.keysym.sym || SDLK_o == sdl->event.key.keysym.sym)
		detail_key(sdl);
	else if (SDLK_g == sdl->event.key.keysym.sym)
		swithc_gloss(sdl);
	else if (SDLK_r == sdl->event.key.keysym.sym || SDLK_f == sdl->event.key.keysym.sym)
		reflection_key(sdl);
	else if (SDLK_e == sdl->event.key.keysym.sym)
		swithc_pref(sdl);
}

void move_key(t_sdl *sdl)
{
	float delta = 10.0;

	sdl->dital = 1;
	if (SDLK_w == sdl->event.key.keysym.sym)
	{
		sdl->cam.rot = (t_vector){sdl->cam.rot.x + delta * sdl->j.x, sdl->cam.rot.y + delta * sdl->j.y, sdl->cam.rot.z + delta * sdl->j.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x + delta * sdl->j.x, sdl->cam.pos.y + delta * sdl->j.y, sdl->cam.pos.z - delta * sdl->j.z};
	}
	else if (SDLK_s == sdl->event.key.keysym.sym)
	{
		sdl->cam.rot = (t_vector){sdl->cam.rot.x - delta * sdl->j.x, sdl->cam.rot.y - delta * sdl->j.y, sdl->cam.rot.z - delta * sdl->j.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x - delta * sdl->j.x, sdl->cam.pos.y - delta * sdl->j.y, sdl->cam.pos.z - delta * sdl->j.z};
	}
	else if (SDLK_a == sdl->event.key.keysym.sym)
	{
		sdl->cam.rot = (t_vector){sdl->cam.rot.x + delta * sdl->i.x, sdl->cam.rot.y + delta * sdl->i.y, sdl->cam.rot.z + delta * sdl->i.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x + delta * sdl->i.x, sdl->cam.pos.y + delta * sdl->i.y, sdl->cam.pos.z + delta * sdl->i.z};
	}
	else if (SDLK_d == sdl->event.key.keysym.sym)
	{
		sdl->cam.rot = (t_vector){sdl->cam.rot.x - delta * sdl->i.x, sdl->cam.rot.y - delta * sdl->i.y, sdl->cam.rot.z - delta * sdl->i.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x - delta * sdl->i.x, sdl->cam.pos.y - delta * sdl->i.y, sdl->cam.pos.z - delta * sdl->i.z};
	}
	else if (SDLK_KP_PLUS == sdl->event.key.keysym.sym)
	{
		sdl->cam.rot = (t_vector){sdl->cam.rot.x + delta * sdl->k.x, sdl->cam.rot.y + delta * sdl->k.y, sdl->cam.rot.z + delta * sdl->k.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x + delta * sdl->k.x, sdl->cam.pos.y + delta * sdl->k.y, sdl->cam.pos.z + delta * sdl->k.z};
	}
	else if (SDLK_KP_MINUS == sdl->event.key.keysym.sym)
	{
		sdl->cam.rot = (t_vector){sdl->cam.rot.x - delta * sdl->k.x, sdl->cam.rot.y - delta * sdl->k.y, sdl->cam.rot.z - delta * sdl->k.z};
		sdl->cam.pos = (t_vector){sdl->cam.pos.x - delta * sdl->k.x, sdl->cam.pos.y - delta * sdl->k.y, sdl->cam.pos.z - delta * sdl->k.z};
	}
	ray_tracing_init(sdl);
}

void rotate_key(t_sdl *sdl)
{
	float alpha = 0.05;
	float tmp;

	sdl->dital = 1;
	if (SDLK_LEFT == sdl->event.key.keysym.sym && (tmp = sdl->cam.pos.x) < 20000)
	{
		sdl->cam.pos.x = sdl->cam.pos.x * cosf(alpha) + sdl->cam.pos.z * sinf(alpha);
		sdl->cam.pos.z = tmp * (-sinf(alpha)) + sdl->cam.pos.z * cosf(alpha);
	}
	else if (SDLK_RIGHT == sdl->event.key.keysym.sym && (tmp = sdl->cam.pos.x) > -20000)
	{
		sdl->cam.pos.x = sdl->cam.pos.x * cosf(-alpha) + sdl->cam.pos.z * sinf(-alpha);
		sdl->cam.pos.z = tmp * (-sinf(-alpha)) + sdl->cam.pos.z * cosf(-alpha);
	}
	else if (SDLK_DOWN == sdl->event.key.keysym.sym && (tmp = sdl->cam.pos.y) > -20000)
	{
		sdl->cam.pos.y = sdl->cam.pos.y * cosf(-alpha) + sdl->cam.pos.z * (-sinf(-alpha));
		sdl->cam.pos.z = tmp * sinf(-alpha) + sdl->cam.pos.z * cosf(-alpha);
	}
	else if (SDLK_UP == sdl->event.key.keysym.sym && (tmp = sdl->cam.pos.y) < 20000)
	{
		sdl->cam.pos.y = sdl->cam.pos.y * cosf(alpha) + sdl->cam.pos.z * (-sinf(alpha));
		sdl->cam.pos.z = tmp * sinf(alpha) + sdl->cam.pos.z * cosf(alpha);
	}
	ray_tracing_init(sdl);
}

void detail_key(t_sdl *sdl)
{
	if (SDLK_p == sdl->event.key.keysym.sym && sdl->dital < 16)
	{
		sdl->dital *= 2;
		ray_tracing_init(sdl);
	}
	else if (SDLK_o == sdl->event.key.keysym.sym && sdl->dital > 1)
	{
		sdl->dital /= 2;
		ray_tracing_init(sdl);
	}
}

void swithc_gloss(t_sdl *sdl)
{
	sdl->gloss_activ = (sdl->gloss_activ == 0)? 1 : 0;
	ray_tracing_init(sdl);
}

void reflection_key(t_sdl *sdl)
{
	if (SDLK_r == sdl->event.key.keysym.sym && sdl->reflect_count < 5)
		sdl->reflect_count++;
	else if (SDLK_f == sdl->event.key.keysym.sym && sdl->reflect_count > 0)
		sdl->reflect_count--;
	ray_tracing_init(sdl);
}

void swithc_pref(t_sdl *sdl)
{
	sdl->pref = (sdl->pref == 0)? 1 : 0;
	ray_tracing_init(sdl);
}