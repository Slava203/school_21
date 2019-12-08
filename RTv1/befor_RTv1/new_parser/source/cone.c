/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:28:05 by daron             #+#    #+#             */
/*   Updated: 2019/10/30 18:55:43 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			ft_add_cyl_cone(t_sdl *sdl, int *k, int name ,int ind)
{
	t_object	*link;

	if (!(link = (t_object*)malloc(sizeof(t_object))))
		kill_all("Can't create object <ft_add_cyl_cone>");
	if (ft_strcmp(sdl->scene[*k + 1], "	{") != 0
		|| ft_strcmp(sdl->scene[*k + 7], "	}") != 0)
		kill_all("Cone not in well format 1 <ft_add_cyl_cone>");
	ft_col_n_pos(sdl, link, *k);
	if (ft_strncmp(sdl->scene[*k + 4], "		rot(", 6) != 0)
		kill_all("Cone not in well format 2 <ft_add_cyl_cone>");
	link->rot.x = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	link->rot.y = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	link->rot.z = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	if (sdl->scene[*k + 4][ind] != ')')
		kill_all("Cone not in well format 3 <ft_add_cyl_cone>");

	if (ft_strncmp(sdl->scene[*k + 5], "		size(", 7) != 0)
		kill_all("Cone not in well format 4 <ft_add_cyl_cone>");
	ind = 7;
	link->r = (double)ft_atoi_n(sdl->scene[*k + 5], &ind) / 10;
	if (sdl->scene[*k + 5][ind] != ')')
		kill_all("Cone not in well format 5 <ft_add_cyl_cone>");

	ind = 6;
	if (ft_strncmp(sdl->scene[*k + 6], "		spc(", 6) != 0)
		kill_all("Cone not in well format 7 <ft_add_cyl_cone>");
	link->specular = ft_atoi_n(sdl->scene[*k + 6], &ind);
	if (sdl->scene[*k + 6][ind] != ')')
		kill_all("Cone not in well format 8 <ft_add_cyl_cone>");

	link->name = name;
	link->next = NULL;
	sdl->obj = ft_add_object_link(sdl, link);
	sdl->light_counter++;
	*k += 8;
}

t_vector get_cone_normal(t_ray *ray, t_object *obj)
{
	double	m;
	t_vector	n;
	t_vector	p;

	m = obj->t * vec_dot(ray->dir, obj->rot) +
		vec_dot(vec_sub(ray->orig, obj->pos), obj->rot);
	p = vec_sum(ray->orig, vec_scale(ray->dir, obj->t));
	n = vec_scale(vec_scale(obj->rot, m), (1 + obj->r * obj->r));
	n = vec_norm(vec_sub(vec_sub(p, obj->pos), n));
	if (vec_dot(ray->dir, n) > EPS)
		n = vec_scale(n, -1);
	return (n);
}

double get_cone_intersection(t_vector cam_pos, t_vector dir, t_object *obj)
{
	double	a;
	double	b;
	double	c;
	double discriminant;
	t_vector	oc;

	oc = vec_sub(cam_pos, obj->pos);
	a = vec_dot(dir, obj->rot);
	a = vec_dot(dir, dir) - (1 + pow(obj->r, 2)) * pow(a, 2);
	b = 2 * (vec_dot(dir, oc) - (1 + pow(obj->r, 2)) * vec_dot(dir, obj->rot) * vec_dot(oc, obj->rot));
	c = vec_dot(oc, oc) - (1 + pow(obj->r, 2)) * pow(vec_dot(oc, obj->rot), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < EPS)
		return (-1);
	return (get_quadratic_solution(a, b, discriminant));
}

void cone_intersection(t_sdl *sdl, t_ray *camera, t_object *obj)
{
	obj->t = get_cone_intersection(camera->orig, camera->dir, obj);
	obj->rot = vec_norm(obj->rot);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = obj;
	}
}