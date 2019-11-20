/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:03:47 by daron             #+#    #+#             */
/*   Updated: 2019/11/17 13:49:32 by daron            ###   ########.fr       */
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

double get_plane_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl)
{
	sdl->t0 = ((vec_dot(&obj->rot, &obj->pos) - vec_dot(&obj->rot, cam_pos)) / vec_dot(&obj->rot, ray_dir));

	if (sdl->t0 < EPS)
		return (-1);
	return (sdl->t0);
}