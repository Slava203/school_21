/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:51:17 by daron             #+#    #+#             */
/*   Updated: 2019/10/31 14:36:19 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			ft_add_sphere(t_sdl *sdl, int *k, int ind)
{
	t_object	*link;

	if (!(link = (t_object*)malloc(sizeof(t_object))))
		kill_all("Can't create object <ft_add_sphere>");
	if (ft_strcmp(sdl->scene[*k + 1], "	{") != 0 || ft_strcmp(sdl->scene[*k + 6], "	}") != 0)
		kill_all("Sphere not in well format 1 <ft_add_sphere>");

	ft_col_n_pos(sdl, link, *k);

	if (ft_strncmp(sdl->scene[*k + 4], "		size(", 7) != 0)
		kill_all("Sphere not in well format 2 <ft_add_sphere>");
	link->r = (double)ft_atoi_n(sdl->scene[*k + 4], &ind) / 10;
	if (sdl->scene[*k + 4][ind] != ')')
		kill_all("Sphere not in well format 3 <ft_add_sphere>");

	ind = 6;
	if (ft_strncmp(sdl->scene[*k + 5], "		spc(", 6) != 0)
		kill_all("Cone not in well format 4 <ft_add_sphere>");
	link->specular = ft_atoi_n(sdl->scene[*k + 5], &ind);
	if (sdl->scene[*k + 5][ind] != ')')
		kill_all("Cone not in well format 5 <ft_add_sphere>");

	link->name = SPHERE_ID;
	link->next = NULL;
	sdl->obj = ft_add_object_link(sdl, link);
	*k += 7;
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

void sphere_intersection(t_sdl *sdl, t_ray *camera, t_object *obj)
{
	obj->t = get_sphere_intersection(camera->orig, camera->dir, obj);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = obj;
	}
}