/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:19:03 by daron             #+#    #+#             */
/*   Updated: 2019/11/17 15:41:28 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double get_cylinder_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl)
{
	double b;
	double c;
	double discriminant;

	sdl->dist = vec_sub(cam_pos, &obj->pos);
	obj->rot = vec_norm(&obj->rot);
	sdl->a = vec_dot(ray_dir, ray_dir) - pow(vec_dot(ray_dir, &obj->rot), 2);
	b = 2 * (vec_dot(ray_dir, &sdl->dist) - (vec_dot(ray_dir, &obj->rot) * vec_dot(&sdl->dist, &obj->rot)));
	c = vec_dot(&sdl->dist, &sdl->dist) - pow(vec_dot(&sdl->dist, &obj->rot), 2) - pow(obj->r, 2);
	discriminant = pow(b, 2) - 4 * sdl->a * c;
	if (discriminant < 0)
		return (-1);
	sdl->t0 = get_quadratic_solution(sdl->a, b, discriminant);
	return (sdl->t0);
}

/*t_vector get_cylinder_normal(t_ray *ray, t_object *obj)
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


void cylinder_intersection(t_sdl *sdl, t_ray *camera,t_object *obj)
{
	obj->t = get_cylinder_intersection(camera->orig, camera->dir, obj);
	obj->rot = vec_norm(obj->rot);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = obj;
	}
}*/