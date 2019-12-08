/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:51:17 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 12:48:58 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void init_sphere(t_sdl *sdl, char **param)
{
	sdl->obj[sdl->obj_counter].pos.x = (double)ft_atoi(param[1]);
	sdl->obj[sdl->obj_counter].pos.y = (double)ft_atoi(param[2]);
	sdl->obj[sdl->obj_counter].pos.z = (double)ft_atoi(param[3]);

	sdl->obj[sdl->obj_counter].rot.x = (double)ft_atoi(param[4]);
	sdl->obj[sdl->obj_counter].rot.y = (double)ft_atoi(param[5]);
	sdl->obj[sdl->obj_counter].rot.z = (double)ft_atoi(param[6]);

	sdl->obj[sdl->obj_counter].r = (double)(ft_atoi(param[4])) / 10;

	if (sdl->obj[sdl->obj_counter].r < 0.1)
		kill_all("Are you kidding, it's small radius <init_sphere>");

	sdl->obj[sdl->obj_counter].col.r = (int)ft_atoi(param[5]);
	sdl->obj[sdl->obj_counter].col.g = (int)ft_atoi(param[6]);
	sdl->obj[sdl->obj_counter].col.b = (int)ft_atoi(param[7]);
	color_validation(&(sdl->obj[sdl->obj_counter].col));

	sdl->obj[sdl->obj_counter].specular = (double)ft_atoi(param[8]);

	sdl->obj[sdl->obj_counter].name = SPHERE_ID;

	sdl->obj_counter++;
}

t_vector get_sphere_normal(t_ray *ray, t_object *obj)
{
	t_vector op;

	op = vec_sum(ray->orig, vec_scale(ray->dir, obj->t));
	op = vec_norm(vec_sub(op, obj->pos));
	if (vec_dot(ray->dir, op) > EPS)
		op = vec_scale(op, -1);
	return (op);
}

double get_sphere_intersection(t_vector cam_pos, t_vector dir, t_object *obj)
{
	double a;
	double b;
	double c;
	double discriminant;
	t_vector oc;

	oc = vec_sub(cam_pos, obj->pos);
	a = vec_dot(dir, dir);
	b = 2 * vec_dot(oc, dir);
	c = vec_dot(oc, oc) - pow(obj->r, 2);//Проверь это место
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (get_quadratic_solution(a, b , discriminant));
}

void sphere_intersection(t_sdl *sdl, t_ray *camera, int i, t_object *obj)
{
	obj->t = get_sphere_intersection(camera->orig, camera->dir, obj);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = i;
	}
}
