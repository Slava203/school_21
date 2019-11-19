/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:51:17 by daron             #+#    #+#             */
/*   Updated: 2019/11/17 13:49:11 by daron            ###   ########.fr       */
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
	link->r = (double)ft_atoi_n(sdl->scene[*k + 4], &ind);
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

double get_sphere_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl)
{
	double b;
	double c;
	double discriminant;

	sdl->dist = vec_sub(cam_pos, &obj->pos);
	sdl->a = vec_dot(ray_dir, ray_dir);
	b = 2 * vec_dot(ray_dir, &sdl->dist);
	c = vec_dot(&sdl->dist, &sdl->dist) - pow(obj->r, 2);//Проверь это место
	discriminant = pow(b, 2) - 4 * sdl->a * c;
	if (discriminant < 0)
		return (-1);
	sdl->t0 = get_quadratic_solution(sdl->a, b , discriminant);
	return (sdl->t0);
}

/*t_vector get_sphere_normal(t_ray *ray, t_object *obj)
{
	t_vector op;

	op = vec_sum(ray->orig, vec_scale(ray->dir, obj->t));
	op = vec_norm(vec_sub(op, obj->pos));
	if (vec_dot(ray->dir, op) > EPS)
		op = vec_scale(op, -1);
	return (op);
}

void sphere_intersection(t_sdl *sdl, t_ray *camera, t_object *obj)
{
	obj->t = get_sphere_intersection(camera->orig, camera->dir, obj);
	if (obj->t > 0 && obj->t < sdl->min_t)
	{
		sdl->min_t = obj->t;
		sdl->clos_obj = obj;
	}
}*/