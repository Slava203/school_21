/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:19:03 by daron             #+#    #+#             */
/*   Updated: 2019/10/25 16:01:52 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector get_cylinder_normal(t_ray *ray, t_object *obj)
{
	double m;
	t_vector n;
	t_vector p;

	m = obj->t * vec_dot(ray->dir, obj->rot) + vec_dot(vec_sub(ray->orig, obj->pos), obj->rot);
	p = vec_sum(ray->orig, vec_scale(ray->dir, obj->t));
	n = vec_norm(vec_sub(vec_sub(p, obj->pos), vec_scale(obj->rot, m)));
	if (vec_dot(ray->dir, n) > EPS)
		n = vec_scale(n , -1);
	return (n);
}

double get_cylinder_intersection(t_vector cam_pos, t_vector dir, t_object *obj)
{
	double a;
	double b;
	double c;
	double discriminant;
	t_vector oc;

	oc = vec_sub(cam_pos, obj->pos);
	a = vec_dot(dir, dir) - pow(vec_dot(dir, obj->rot), 2);
	b = 2 * (vec_dot(dir, oc) - (vec_dot(dir, obj->rot) * vec_dot(oc, obj->rot)));
	c = vec_dot(oc, oc) - pow(vec_dot(oc, obj->rot), 2) - pow(obj->r, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b , discriminant));
}

void cylinder_intersection(t_sdl *sdl, t_ray *camera,t_object *obj)
{
	obj->t = get_cylinder_intersection(camera->orig, camera->dir, obj);
	obj->rot = vec_norm(obj->rot);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = obj;
	}
}