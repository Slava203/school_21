/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:31:50 by daron             #+#    #+#             */
/*   Updated: 2019/10/27 13:25:28 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void init_light(t_sdl *sdl, char **param)
{
	sdl->light[sdl->light_counter].pos.x = (double)ft_atoi(param[1]);
	sdl->light[sdl->light_counter].pos.y = (double)ft_atoi(param[2]);
	sdl->light[sdl->light_counter].pos.z = (double)ft_atoi(param[3]);

	sdl->light[sdl->light_counter].inten = (double)ft_atoi(param[4]) / 100;

	if (sdl->light[sdl->light_counter].inten < 0)
		kill_all("Are you kidding, it can't be lover then zero <init_light>");
	sdl->light_counter++;
}

static int		shadow_init(t_light *light, t_sdl *sdl) // смотрим еть ли в точке тень
{
	int		ind;
	double	max_t;
	double	t;
	t_vector	dir;

	ind = 0;
	t = 0;
	max_t = vec_len(vec_sub(light->pos, light->p));
	dir = vec_norm(vec_sub(light->pos, light->p));
	light->p = vec_sum(light->p, vec_scale(dir, EPS));
	while (ind < sdl->obj_num)
	{
		if (sdl->obj[ind].name == SPHERE_ID)
			t = get_sphere_intersection(light->p, dir, &sdl->obj[ind]);
		else if (sdl->obj[ind].name == PLANE_ID)
			t = get_plane_intersection(light->p, dir, &sdl->obj[ind]);
		else if (sdl->obj[ind].name == CONE_ID)
			t = get_cone_intersection(light->p, dir, &sdl->obj[ind]);
		else if (sdl->obj[ind].name == CYLINDER_ID)
			t = get_cylinder_intersection(light->p, dir, &sdl->obj[ind]);
		if (t > EPS && t < max_t)
			return (1);
		ind++;
	}
	return (0);
}

/*
 ** v - normal vector
 ** s - specular
 */
static void get_intensity(t_sdl *sdl, t_light *light, t_vector v, double s) // расчитываем интенсивность точки и ее отражательный эффект
{
	double	n_dot_l;
	double	r_dot_v;

	double	inten;

	t_vector	l;
	t_vector	r;

	inten = 0.0;
	light->new_inten = sdl->ambient;
	l = vec_norm(vec_sub(light->pos, light->p));
	n_dot_l = vec_dot(light->n, l);
	//printf("n_dot_l = %g\n", n_dot_l);
	if (shadow_init(light, sdl) == 0)
		inten = light->inten;
	if (n_dot_l > EPS)
		light->new_inten += inten * (n_dot_l / (vec_len(light->n) * vec_len(l)));
	//printf("light->new_inten = %g\n", light->new_inten);
	if (s > 0)
	{
		r = vec_scale(light->n, 2);
		r = vec_scale(r, vec_dot(light->n, l));
		r = vec_sub(r, l);
		r_dot_v = vec_dot(r, v);
		if (r_dot_v > EPS)
			light->new_inten += inten * pow((r_dot_v / (vec_len(r) * vec_len(v))), s);
	}
}

void light(t_sdl *sdl, t_ray *ray) // находим нормаль к объекту с которым есть пересечение в текущей точке
{
	int ind;

	ind = 0;
	if (sdl->clos_obj > -1)
	{
		while (ind < sdl->light_num)
		{
			//printf("ray->dir = (%g %g %g)\n", ray->dir.x, ray->dir.y, ray->dir.z);
			sdl->light[ind].p = vec_sum(ray->orig, vec_scale(ray->dir, sdl->obj[sdl->clos_obj].t));// луч исходящий из точки камеры
			//printf("sdl->light[ind].p = (%g %g %g)\n", sdl->light[ind].p.x, sdl->light[ind].p.y, sdl->light[ind].p.z);
			//printf("ray->orig = (%g %g %g)\n", ray->orig.x, ray->orig.y, ray->orig.z);
			//printf("ray->dir = (%g %g %g)\n", ray->dir.x, ray->dir.y, ray->dir.z);
			if (sdl->obj[sdl->clos_obj].name == SPHERE_ID)
				sdl->light[ind].n = get_sphere_normal(ray, &sdl->obj[sdl->clos_obj]);
			else if (sdl->obj[sdl->clos_obj].name == PLANE_ID)
				sdl->light[ind].n = get_plane_normal(ray, &sdl->obj[sdl->clos_obj]);
			else if (sdl->obj[sdl->clos_obj].name == CYLINDER_ID)
				sdl->light[ind].n = get_cylinder_normal(ray, &sdl->obj[sdl->clos_obj]);
			else if (sdl->obj[sdl->clos_obj].name == CONE_ID)
				sdl->light[ind].n = get_cone_normal(ray, &sdl->obj[sdl->clos_obj]);
			get_intensity(sdl, &sdl->light[ind], vec_scale(ray->dir, -1), sdl->obj[sdl->clos_obj].specular);
			ind++;
		}
	}
}
