/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:30:37 by daron             #+#    #+#             */
/*   Updated: 2019/11/22 14:36:38 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	create_guide_sides(t_move *move, t_sdl *sdl)
{
	move->k = vec_sub(&SC.rot, &SC.pos);
	move->k = vec_norm(&move->k);
	move->i = vec_cross(&move->k, &(t_vector){0.0, 1.0, 0.0});
	move->i = vec_norm(&move->i);
	move->j = vec_cross(&move->i, &move->k);
}

static void	event_2(t_sdl *sdl, t_move *move)
{
	if (SDLK_e == SEKKS && sdl->event.type == SDL_KEYDOWN)
		swithc_pref(sdl);
	else if (sdl->event.type == SDL_KEYDOWN && SSO == NULL)
		key_down(sdl, move);
	else if (sdl->event.type == SDL_KEYDOWN && SSO != NULL)
		key_down_for_object(sdl, move);
	else if (sdl->event.type == SDL_MOUSEBUTTONDOWN)
		mouse_down(sdl);
}

void		events(t_sdl *sdl)
{
	t_move	move;

	create_guide_sides(&move, sdl);
	while (1)
		while (SDL_PollEvent(&sdl->event))
		{
			if ((SDL_QUIT == sdl->event.type) ||
				(SDL_SCANCODE_ESCAPE == sdl->event.key.keysym.scancode))
			{
				printf("Camera pos = {%g %g %g}\n rot = {%g %g %g}\n\n",
						sdl->cam.pos.x, sdl->cam.pos.y, sdl->cam.pos.z,
						sdl->cam.rot.x, sdl->cam.rot.y, sdl->cam.rot.z);
				printf("Ambient = %g\n\n", sdl->ambient);
				t_light *light;
				light = sdl->light;
				while (light)
				{
					printf("Light pos = {%g %g %g}\n color = {%g %g %g}\n intent = %g\n\n",
						   light->pos.x, light->pos.y, light->pos.z,
						   light->col.r, light->col.g, light->col.b,
						   light->inten);
					light = light->next;
				}
				t_object *object;
				object = sdl->obj;
				while (object)
				{
					if (object->name == CYLINDER_ID || object->name == CONE_ID)
						printf("Object_id = %d, pos = {%g %g %g}\n rot = {%g %g %g} color = {%g %g %g}\n r = %g specular = %g\n\n",
							   object->name, object->pos.x,object->pos.y, object->pos.z,
							   object->rot.x, object->rot.y, object->rot.z,
							   object->col.r, object->col.g, object->col.b,
							   object->r, object->specular);
					else if (object->name == PLANE_ID)
						printf("Object_id = %d, pos = {%g %g %g}\n rot = {%g %g %g} color = {%g %g %g}\n specular = %g\n\n",
							   object->name, object->pos.x,object->pos.y, object->pos.z,
							   object->rot.x, object->rot.y, object->rot.z,
							   object->col.r, object->col.g, object->col.b,
							   object->specular);
					else if (object->name == SPHERE_ID)
						printf("Object_id = %d, pos = {%g %g %g}\n r = %g color = {%g %g %g}\n specular = %g\n\n",
							   object->name, object->pos.x,object->pos.y, object->pos.z,
							   object->r, object->col.r, object->col.g, object->col.b,
							   object->specular);

					object = object->next;
				}

				my_free(sdl);
				exit(0);
			}
			else if (SDLK_RETURN == SEKKS && sdl->event.type == SDL_KEYDOWN)
				SSO = NULL;
			else if ((SDLK_p == SEKKS || SDLK_o == SEKKS)
						&& sdl->event.type == SDL_KEYDOWN)
				detail_key(sdl);
			else if (SDLK_g == SEKKS && sdl->event.type == SDL_KEYDOWN)
				swithc_gloss(sdl);
			else if ((SDLK_r == SEKKS || SDLK_f == SEKKS)
						&& sdl->event.type == SDL_KEYDOWN)
				reflection_key(sdl);
			else
				event_2(sdl, &move);
		}
}
