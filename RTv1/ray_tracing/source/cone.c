/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:28:05 by daron             #+#    #+#             */
/*   Updated: 2019/10/23 16:36:43 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void init_cone(t_sdl *sdl, char **param)
{
	sdl->obj[sdl->obj_counter].pos.x = (double)ft_atoi(param[1]);
	sdl->obj[sdl->obj_counter].pos.y = (double)ft_atoi(param[2]);
	sdl->obj[sdl->obj_counter].pos.z = (double)ft_atoi(param[3]);

	sdl->obj[sdl->obj_counter].r = (double)(ft_atoi(param[4])) / 10;

	if (sdl->obj[sdl->obj_counter].r < 0.1)
		kill_all("Are you kidding, it's small radius <init_cone>");

	sdl->obj[sdl->obj_counter].rot.x = (double)ft_atoi(param[5]);
	sdl->obj[sdl->obj_counter].rot.y = (double)ft_atoi(param[6]);
	sdl->obj[sdl->obj_counter].rot.z = (double)ft_atoi(param[7]);

	sdl->obj[sdl->obj_counter].col.r = (int)ft_atoi(param[8]);
	sdl->obj[sdl->obj_counter].col.g = (int)ft_atoi(param[9]);
	sdl->obj[sdl->obj_counter].col.b = (int)ft_atoi(param[10]);
	color_validation(&(sdl->obj[sdl->obj_counter].col));

	sdl->obj[sdl->obj_counter].specular = (double)ft_atoi(param[11]);

	sdl->obj[sdl->obj_counter].name = CONE_ID;

	sdl->obj_counter++;
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

void cone_intersection(t_sdl *sdl, t_ray *camera, int i, t_object *obj)
{
	obj->t = get_cone_intersection(camera->orig, camera->dir, obj);
	obj->rot = vec_norm(obj->rot);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = i;
	}
}