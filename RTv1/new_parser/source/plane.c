/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:03:47 by daron             #+#    #+#             */
/*   Updated: 2019/10/30 19:53:17 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			ft_add_plane(t_sdl *sdl, int *k, int ind)
{
	t_object	*link;

	if (!(link = (t_object*)malloc(sizeof(t_object))))
		kill_all("Can't create object <ft_add_cyl_cone>");

	if (ft_strcmp(sdl->scene[*k + 1], "	{") != 0 || ft_strcmp(sdl->scene[*k + 6], "	}") != 0)
		kill_all("Plane not in well format 1 <ft_add_cyl_cone>");
	ft_col_n_pos(sdl, link, *k);
	if (ft_strncmp(sdl->scene[*k + 4], "		rot(", 6) != 0)
		kill_all("Plane not in well format 2 <ft_add_cyl_cone>");
	link->rot.x = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	link->rot.y = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	link->rot.z = (float)ft_atoi_n(sdl->scene[*k + 4], &ind);
	if (sdl->scene[*k + 4][ind] != ')')
		kill_all("Plane not in well format 3 <ft_add_cyl_cone>");

	ind = 6;
	if (ft_strncmp(sdl->scene[*k + 5], "		spc(", 6) != 0)
		kill_all("Cone not in well format 7 <ft_add_cyl_cone>");
	link->specular = ft_atoi_n(sdl->scene[*k + 5], &ind);
	if (sdl->scene[*k + 5][ind] != ')')
		kill_all("Cone not in well format 8 <ft_add_cyl_cone>");

	link->next = NULL;
	link->name = PLANE_ID;
	sdl->obj = ft_add_object_link(sdl, link);
	*k += 7;
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

void plane_intersection(t_sdl *sdl, t_ray *camera, t_object *obj)
{
	obj->rot = vec_norm(obj->rot);
	obj->t = get_plane_intersection(camera->orig, camera->dir, obj);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = obj;
	}
}