/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:08:56 by daron             #+#    #+#             */
/*   Updated: 2019/11/19 14:44:58 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

float   ft_clamp(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}


void my_free(t_sdl *sdl)
{
	t_object *obj;
	t_object *obj_next;
	t_light *light;
	t_light *light_next;
	int ind;

	obj = sdl->obj;
	while (obj)
	{
		obj_next = obj->next;
		free(obj);
		obj = obj_next;
	}

	light = sdl->light;
	while (light)
	{
		light_next = light->next;
		free(light);
		light = light_next;
	}

	ind = -1;
	while (++ind < sdl->line_count)
		free(sdl->scene[ind]);
	free(sdl->scene);

	SDL_DestroyRenderer(sdl->render);
	SDL_DestroyWindow(sdl->window);
}

double	get_quadratic_solution(double a, double b, double discriminant)
{
	double t1;
	double t2;

	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
		return (t2);
	return (-1);
}

int				kill_all(char *message)
{
	perror(message);
	//ft_putstr(message);
	exit(1);
}

void sdl_initialize(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		kill_all("Can't initialize SDL <sdl_initialize>");
	if (!(sdl->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN)))
		kill_all("Can't initialize Window <sdl_initialize>");
	if (!(sdl->render = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED)))
		kill_all("Can't render Window <sdl_initialize>");
}

int main(int argc, char **argv)
{
	t_sdl sdl;

	sdl_initialize(&sdl);

	if (argc != 2 || !argv[1])
		kill_all("usage: ./RTv1 scene_name");
	scene_parser(&sdl, argv[1]);

	ray_tracing_init(&sdl);

	/*printf("Camera pos = {%g %g %g}\n rot = {%g %g %g}\n\n", sdl.cam.pos.x, sdl.cam.pos.y, sdl.cam.pos.z, sdl.cam.rot.x, sdl.cam.rot.y, sdl.cam.rot.z);
	printf("Ambient = %g\n\n", sdl.ambient);

	t_light *light;

	light = sdl.light;
	while (light)
	{
		printf("Light pos = {%g %g %g}\n color = {%g %g %g}\n intent = %g\n\n",
			   light->pos.x, light->pos.y, light->pos.z,
			   light->col.r, light->col.g, light->col.b,
			   light->inten);
		light = light->next;
	}

	t_object *object;

	object = sdl.obj;
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
	*/
	events(&sdl);

	return (0);
}