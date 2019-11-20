/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:28:05 by daron             #+#    #+#             */
/*   Updated: 2019/11/17 15:40:17 by daron            ###   ########.fr       */
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
	link->r = (double)ft_atoi_n(sdl->scene[*k + 5], &ind);
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
	*k += 8;
}

double get_cone_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl)
{
	double	b;
	double	c;
	double	a;
	double discriminant;

	sdl->dist = vec_sub(cam_pos, &obj->pos);
	obj->rot = vec_norm(&obj->rot);
	a = vec_dot(ray_dir, ray_dir) - (1 + pow(tan(obj->r), 2)) * pow(vec_dot(ray_dir, &obj->rot), 2);
	b = 2 * (vec_dot(ray_dir, &sdl->dist) - (1 + pow(tan(obj->r), 2)) * vec_dot(ray_dir, &obj->rot) * vec_dot(&sdl->dist, &obj->rot));
	c = vec_dot(&sdl->dist, &sdl->dist) - (1 + pow(tan(obj->r), 2)) * pow(vec_dot(&sdl->dist, &obj->rot), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	sdl->t0 = get_quadratic_solution(a, b, discriminant);
	return (sdl->t0);
}