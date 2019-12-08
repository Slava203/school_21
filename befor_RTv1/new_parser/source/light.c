/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:31:50 by daron             #+#    #+#             */
/*   Updated: 2019/10/31 17:32:46 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_add_light(t_sdl *sdl, int *k, int ind)
{
	t_light	*link;

	if (!(link = (t_light*)malloc(sizeof(t_light))))
		kill_all("Can't create light <ft_add_light>");
	if (ft_strcmp(sdl->scene[*k + 1], "	{") != 0 || ft_strcmp(sdl->scene[*k + 5], "	}") != 0)
		kill_all("Light not in well format 1 <ft_add_light>");
	if (ft_strncmp(sdl->scene[*k + 2], "		col(", 6) != 0 ||
		ft_strncmp(sdl->scene[*k + 3], "		pos(", 6) != 0 ||
		ft_strncmp(sdl->scene[*k + 4], "		int(", 6) != 0)
		kill_all("Light not in well format 2 <ft_add_light>");
	link->col.r = ft_atoi_n(sdl->scene[*k + 2], &ind);
	link->col.g = ft_atoi_n(sdl->scene[*k + 2], &ind);
	link->col.b = ft_atoi_n(sdl->scene[*k + 2], &ind);
	if (sdl->scene[*k + 2][ind] != ')')
		kill_all("Light not in well format 3 <ft_add_light>");

	ind = 6;
	link->pos.x = ft_atoi_n(sdl->scene[*k + 3], &ind);
	link->pos.y = ft_atoi_n(sdl->scene[*k + 3], &ind);
	link->pos.z = ft_atoi_n(sdl->scene[*k + 3], &ind);
	if (sdl->scene[*k + 3][ind] != ')')
		kill_all("Light not in well format 4 <ft_add_light>");

	ind = 6;
	link->inten = (double)ft_atoi_n(sdl->scene[*k + 4], &ind) / 100;
	if (sdl->scene[*k + 4][ind] != ')')
		kill_all("Light not in well format 5 <ft_add_light>");

	link->next = NULL;
	sdl->light_counter++;
	sdl->light = ft_add_light_link(sdl, link);
	*k += 6;
}

static int		shadow_init(t_light *light, t_sdl *sdl) // смотрим еть ли в точке тень
{
	double	max_t;
	double	t;
	t_vector	dir;
	t_object *obj;

	t = 0;
	max_t = vec_len(vec_sub(light->pos, light->p));
	dir = vec_norm(vec_sub(light->pos, light->p));
	light->p = vec_sum(light->p, vec_scale(dir, EPS));
	obj = sdl->obj;
	while (obj)
	{
		if (obj->name == SPHERE_ID)
			t = get_sphere_intersection(light->p, dir, obj);
		else if (obj->name == PLANE_ID)
			t = get_plane_intersection(light->p, dir, obj);
		else if (obj->name == CONE_ID)
			t = get_cone_intersection(light->p, dir, obj);
		else if (obj->name == CYLINDER_ID)
			t = get_cylinder_intersection(light->p, dir, obj);
		if (t > EPS && t < max_t)
			return (1);
		obj = obj->next;
	}
	return (0);
}

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
	t_light *light;

	light = sdl->light;
	if (sdl->clos_obj != NULL)
	{
		while (light)
		{
			//printf("ray->dir = (%g %g %g)\n", ray->dir.x, ray->dir.y, ray->dir.z);
			light->p = vec_sum(ray->orig, vec_scale(ray->dir, sdl->clos_obj->t));// луч исходящий из точки камеры
			//printf("sdl->light[ind].p = (%g %g %g)\n", sdl->light[ind].p.x, sdl->light[ind].p.y, sdl->light[ind].p.z);
			//printf("ray->orig = (%g %g %g)\n", ray->orig.x, ray->orig.y, ray->orig.z);
			//printf("ray->dir = (%g %g %g)\n", ray->dir.x, ray->dir.y, ray->dir.z);

			if (sdl->clos_obj->name == SPHERE_ID)
				light->n = get_sphere_normal(ray, sdl->clos_obj);
			else if (sdl->clos_obj->name == PLANE_ID)
				light->n = get_plane_normal(ray, sdl->clos_obj);
			else if (sdl->clos_obj->name == CYLINDER_ID)
				light->n = get_cylinder_normal(ray, sdl->clos_obj);
			else if (sdl->clos_obj->name == CONE_ID)
				light->n = get_cone_normal(ray, sdl->clos_obj);

			get_intensity(sdl, light, vec_scale(ray->dir, -1), sdl->clos_obj->specular);
			light = light->next;
		}
	}
}
