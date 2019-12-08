/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:19:03 by daron             #+#    #+#             */
/*   Updated: 2019/11/20 15:54:43 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double get_cylinder_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl)
{
	double b;
	double c;
	double a;
	double discriminant;

	sdl->dist = vec_sub(cam_pos, &obj->pos);
	obj->rot = vec_norm(&obj->rot);
	a = vec_dot(ray_dir, ray_dir) - pow(vec_dot(ray_dir, &obj->rot), 2);
	b = 2 * (vec_dot(ray_dir, &sdl->dist) - (vec_dot(ray_dir, &obj->rot) * vec_dot(&sdl->dist, &obj->rot)));
	c = vec_dot(&sdl->dist, &sdl->dist) - pow(vec_dot(&sdl->dist, &obj->rot), 2) - pow(obj->r, 2);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	sdl->t0 = get_quadratic_solution(a, b, discriminant);
	return (sdl->t0);
}