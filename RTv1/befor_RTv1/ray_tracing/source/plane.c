/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:03:47 by daron             #+#    #+#             */
/*   Updated: 2019/10/23 16:29:26 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void init_plane(t_sdl *sdl, char **param)
{
	sdl->obj[sdl->obj_counter].pos.x = (double)ft_atoi(param[1]);
	sdl->obj[sdl->obj_counter].pos.y = (double)ft_atoi(param[2]);
	sdl->obj[sdl->obj_counter].pos.z = (double)ft_atoi(param[3]);

	sdl->obj[sdl->obj_counter].rot.x = (double)ft_atoi(param[4]);
	sdl->obj[sdl->obj_counter].rot.y = (double)ft_atoi(param[5]);
	sdl->obj[sdl->obj_counter].rot.z = (double)ft_atoi(param[6]);

	sdl->obj[sdl->obj_counter].col.r = (int)ft_atoi(param[7]);
	sdl->obj[sdl->obj_counter].col.g = (int)ft_atoi(param[8]);
	sdl->obj[sdl->obj_counter].col.b = (int)ft_atoi(param[9]);
	color_validation(&(sdl->obj[sdl->obj_counter].col));

	sdl->obj[sdl->obj_counter].specular = (double)ft_atoi(param[10]);

	sdl->obj[sdl->obj_counter].name = PLANE_ID;

	sdl->obj_counter++;
}

t_vector get_plane_normal(t_ray *ray, t_object *obj)
{
	if (vec_dot(ray->dir, obj->rot) < 0)
		return (obj->rot);
	else
		return (vec_scale(obj->rot, -1));
}

double get_plane_intersection(t_vector cam_pos, t_vector dir, t_object *obj)
{
	double a;
	double b;
	double t;
	t_vector oc;

	oc = vec_sub(cam_pos, obj->pos);
	a = vec_dot(oc, obj->rot);
	b = vec_dot(dir, obj->rot);

	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (-1);
	t = -a / b;
	if (t > EPS)
		return (t);
	else
		return (-1);
}

void plane_intersection(t_sdl *sdl, t_ray *camera, int i, t_object *obj)
{
	obj->rot = vec_norm(obj->rot);
	obj->t = get_plane_intersection(camera->orig, camera->dir, obj);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = i;
	}
}