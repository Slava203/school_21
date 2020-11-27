/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:38:16 by daron             #+#    #+#             */
/*   Updated: 2019/11/15 12:07:44 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void get_direction(t_point point, t_ray *ray, t_sdl *sdl) // задаем напрвление луча чтобы он смотрел в заданный пиксель
{
	ray->dir.x = point.x * (V_WIDTH / (double)W_WIDTH);
	ray->dir.y = point.y * (V_HEIGHT / (double)W_HEIGHT);
	ray->dir.z = 1.0;
	//printf("ray->dir = (%g %g %g)\n", ray->dir.x, ray->dir.y, ray->dir.z);
	//printf("point = {%g %g} dir = {%g %g %g}\n", point.x, point.y, ray->dir.x, ray->dir.y, ray->dir.z);
	ray->dir = vec_rot_xyz(ray->dir, sdl->cam.rot);
	//printf("ray->dir = (%g %g %g)\n", ray->dir.x, ray->dir.y, ray->dir.z);
}

void set_color(t_sdl *sdl, int ind, int x, int y) // задаем и выводим цвет фигуры в заисимости от интенсивности точки которую мы получили
{
	double p;
	int k;

	k = 0;
	p = 0;
	while (k < sdl->light_num)
	{
		//printf("ligth_num = %d new_item = %g\n", k, sdl->light[k].new_inten);
		if (sdl->light[k].new_inten > 1)
			sdl->light[k].new_inten = 1;
		p += sdl->light[k].new_inten;
		if (p > 1)
			p = 1;
		k++;
	}
	//printf("p = %g\n", p);
	if (ind > -1)
		SDL_SetRenderDrawColor(sdl->render, sdl->obj[ind].col.r * p, sdl->obj[ind].col.g * p, sdl->obj[ind].col.b * p, 255);
	else
		SDL_SetRenderDrawColor(sdl->render, 0, 0, 0, 255);

	SDL_RenderDrawPoint(sdl->render, x, y);
}

void intersection(t_ray *ray, t_sdl *sdl, int x, int y) // нахождения пересечения луча с объектами
{
	int obj_ind;

	obj_ind = 0;
	sdl->clos_obj = -1;
	sdl->min_t = INFINITY;
	while (obj_ind < sdl->obj_num)
	{
		if (sdl->obj[obj_ind].name == SPHERE_ID)
			sphere_intersection(sdl, ray, obj_ind, &sdl->obj[obj_ind]);
		else if (sdl->obj[obj_ind].name == PLANE_ID)
			plane_intersection(sdl, ray, obj_ind, &sdl->obj[obj_ind]);
		else if (sdl->obj[obj_ind].name == CYLINDER_ID)
			cylinder_intersection(sdl, ray, obj_ind, &sdl->obj[obj_ind]);
		else if (sdl->obj[obj_ind].name == CONE_ID)
			cone_intersection(sdl, ray, obj_ind, &sdl->obj[obj_ind]);
		obj_ind++;
		//printf("sdl->clos_obj = %d sdl->obj = %g\n",sdl->clos_obj, sdl->obj->t);
	}
	//printf("ray->dir = (%g %g %g)\n", ray->dir.x, ray->dir.y, ray->dir.z);
	if (sdl->clos_obj > -1) {
		//printf("ray->dir = (%g %g %g)\n", ray->dir.x, ray->dir.y, ray->dir.z);
		light(sdl, ray);
	}
	//printf("ray = (%g %g %g) ", ray->dir.x, ray->dir.y, ray->dir.z);
	set_color(sdl, sdl->clos_obj, x, y);
	//printf("sdl->clos_obj->t = %g\n", sdl->obj[sdl->clos_obj].t);
}

void ray_tracing_init(t_sdl *sdl, t_ray *ray) // расчет направления луча идущего из камеры в заданный пиксель
{
	int x;
	int y;
	double scaling_x;
	double scaling_y;

	x = 0;
	while (x <= W_WIDTH)
	{
		y = 0;
		scaling_x = 2 * ((x + 0.5) / (double)W_WIDTH) - 1;
		while (y <= W_HEIGHT)
		{
			scaling_y = 1 - 2 * ((y + 0.5) / (double)W_HEIGHT);
			get_direction(init_point(scaling_x, scaling_y), ray, sdl);
			intersection(ray, sdl, x, y);
			y++;
		}
		x++;
	}
}
