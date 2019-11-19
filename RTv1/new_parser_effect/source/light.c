/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:31:50 by daron             #+#    #+#             */
/*   Updated: 2019/11/19 15:11:26 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_add_light(t_sdl *sdl, int *k, int ind)
{
	t_light	*link;

	if (!(link = (t_light*)malloc(sizeof(t_light))))
		kill_all("Can't create light <ft_add_light>");
	if (ft_strcmp(sdl->scene[*k + 1], "	{") != 0 || ft_strcmp(sdl->scene[*k + 5], "	}") != 0)
		kill_all("Light not in well format 1 <ft_add_light>");
	if (ft_strncmp(sdl->scene[*k + 2], "		col(", 6) != 0 ||
		ft_strncmp(sdl->scene[*k + 3], "		pos(", 6) != 0 ||
		ft_strncmp(sdl->scene[*k + 4], "		int(", 6) != 0)
		kill_all("Light not in well format 2 <ft_add_light>");
	link->col.r = ft_atoi_n(sdl->scene[*k + 2], &ind);
	link->col.g = ft_atoi_n(sdl->scene[*k + 2], &ind);
	link->col.b = ft_atoi_n(sdl->scene[*k + 2], &ind);
	if (sdl->scene[*k + 2][ind] != ')')
		kill_all("Light not in well format 3 <ft_add_light>");

	ind = 6;
	link->pos.x = ft_atoi_n(sdl->scene[*k + 3], &ind);
	link->pos.y = ft_atoi_n(sdl->scene[*k + 3], &ind);
	link->pos.z = ft_atoi_n(sdl->scene[*k + 3], &ind);
	if (sdl->scene[*k + 3][ind] != ')')
		kill_all("Light not in well format 4 <ft_add_light>");

	ind = 6;
	link->inten = (double)ft_atoi_n(sdl->scene[*k + 4], &ind) / 100;
	if (sdl->scene[*k + 4][ind] != ')')
		kill_all("Light not in well format 5 <ft_add_light>");

	link->next = NULL;
	sdl->light_counter++;
	sdl->light = ft_add_light_link(sdl, link);
	*k += 6;
}

t_vector object_norm(t_sdl *sdl, t_object *obj, t_vector pos)
{
	t_vector norm;
	t_vector tmp;
	t_vector tmp2;


	if (obj->name == CONE_ID || obj->name == CYLINDER_ID)
	{
		tmp = vec_scale(&obj->rot, (vec_dot(&sdl->ray_dir, &obj->rot) * sdl->t + vec_dot(&sdl->dist, &obj->rot)));
		if (obj->name == CONE_ID)
			tmp = vec_scale(&tmp, (1 + pow(tan(obj->r), 2)));
		tmp2 = vec_sub(&pos, &obj->pos);
		norm = vec_sub(&tmp2, &tmp);
	}
	else if (obj->name == PLANE_ID)
		norm = obj->rot;
	else if (obj->name == SPHERE_ID)
		norm = vec_sub(&pos, &obj->pos);
	return (vec_norm(&norm));
}

int		shadow(t_sdl *sdl, t_object *obj, t_light *light, t_vector pos)
{
	t_object	*head;
	t_vector	dist;

	head = sdl->obj;
	dist = vec_sub(&light->pos, &pos);
	sdl->t = sqrtf(vec_dot(&dist, &dist));
	dist = vec_norm(&dist);
	while (head != NULL)
	{
		if (head != obj)
		{
			if (head->name == SPHERE_ID)
				sdl->a = get_sphere_intersection(&dist, &pos, head, sdl);
			else if (head->name == CYLINDER_ID)
				sdl->a = get_cylinder_intersection(&dist, &pos, head, sdl);
			else if (head->name == CONE_ID)
				sdl->a = get_cone_intersection(&dist, &pos, head, sdl);
			else if (head->name == PLANE_ID)
				sdl->a = get_plane_intersection(&dist, &pos, head, sdl);
			if (sdl->a > 0.0001 && sdl->a < sdl->t)
				return (1);
		}
		head = head->next;
	}
	return (0);
}

float *transfer_light(t_object *obj, t_light *light, float *tab, float d)
{
	tab[3] = ft_clamp(tab[3] * 4.0 * d, 0.0, 1.0);
	tab[0] += tab[3] * (obj->col.r / 255) * (light->col.r / 255);
	tab[1] += tab[3] * (obj->col.g / 255) * (light->col.g / 255);
	tab[2] += tab[3] * (obj->col.b / 255) * (light->col.b / 255);
	//printf("obj.col = (%g %g %g) light.col = (%g %g %g)\n", obj->col.r, obj->col.g, obj->col.b, light->col.r, light->col.g, light->col.b);
	//printf("tab[] = (%g %g %g %g)\n",tab[0], tab[1], tab[2], tab[3]);
	//printf("%g %g %g\n\n", (float)(tab[3] * (obj->col.r / 255) * (light->col.r / 255)), tab[3] * (obj->col.g / 255) * (light->col.g / 255), tab[3] * (obj->col.b / 255) * (light->col.b / 255));
	return (tab);
}

float *gloss(t_sdl *sdl, t_object *obj, float *tab, t_vector *dist, float d)
{
	float	spec;
	float	tmp;
	t_vector	ref;

	if (obj->name != PLANE_ID && sdl->gloss_activ == 1)
	{
		spec = 0.0;
		ref = vec_scale(&sdl->norm, (2.0 * vec_dot(&sdl->norm, dist)));
		ref = vec_sub(dist, &ref);
		tmp = vec_dot(&ref, &sdl->ray_dir);
		if (tmp > 0.0 && tab[3] > sdl->ambient)
		{
			spec = pow(tmp, obj->specular) * 4 * d;
			spec = ft_clamp(spec, 0.0, 1.0);
		}
		//printf("spec = %g\n", spec);
		tab[1] += spec;
		tab[2] += spec;
		tab[3] += spec;
	}
	return (tab);
}

t_object	*ref_inter(t_sdl *sdl, t_object *head, t_object *cur_obj, t_vector pos)
{
	t_object	*tmp2;
	double	dist;

	tmp2 = NULL;
	while (head != NULL)
	{
		if (head != cur_obj)
		{
			if (head->name == SPHERE_ID)
				dist = get_sphere_intersection(&sdl->ref, &pos, head, sdl);
			else if (head->name == CYLINDER_ID)
				dist = get_cylinder_intersection(&sdl->ref, &pos, head, sdl);
			else if (head->name == CONE_ID)
				dist = get_cone_intersection(&sdl->ref, &pos, head, sdl);
			else if (head->name == PLANE_ID)
				dist = get_plane_intersection(&sdl->ref, &pos, head, sdl);
			if (dist > EPS && dist < sdl->t)
			{
				tmp2 = head;
				sdl->t = dist;
			}
		}
		head = head->next;
	}
	return (tmp2);
}

t_object	*ref_init(t_sdl *sdl, t_object *obj, t_vector *pos)
{
	t_object	*tmp2;

	sdl->t = 8000.0;
	sdl->ref = vec_scale(&sdl->norm, (2 * vec_dot(&sdl->refpos, &sdl->norm)));
	sdl->ref = vec_sub(&sdl->refpos, &sdl->ref);
	sdl->ref = vec_norm(&sdl->ref);
	tmp2 = ref_inter(sdl, sdl->obj, obj, *pos);
	if (!tmp2)
		return (NULL);
	*pos = (t_vector){pos->x + sdl->t * sdl->ref.x, pos->y + sdl->t * sdl->ref.y, pos->z + sdl->t * sdl->ref.z};
	sdl->refpos = (t_vector){sdl->ref.x, sdl->ref.y, sdl->ref.z};
	sdl->norm = object_norm(sdl, tmp2, *pos);
	return (tmp2);
}

float *reflection(t_sdl *sdl, t_object *obj, t_vector *pos, float *tab)
{
	t_object	*tmp2;
	t_light		*light;
	t_vector	dist;
	double	d;

	if (sdl->cpt >= sdl->reflect_count || (light = sdl->light) == NULL)
		return (tab);
	if ((tmp2 = ref_init(sdl, obj, pos)) == NULL || (sdl->cpt++) < 0)
		return(tab);
	while (light != NULL)
	{
		tab[3] = sdl->ambient;
		dist = vec_sub(&light->pos, pos);
		d = ft_clamp(1.0 / sqrtf(sqrtf(vec_dot(&dist, &dist))), 0.0, 1.0);
		dist = vec_norm(&dist);
		if (shadow(sdl, tmp2, light, *pos) == 0)
			tab[3] += ft_clamp(vec_dot(&dist, &sdl->norm), 0.0, 1.0);
		tab = transfer_light(tmp2, light, tab, d);
		tab = gloss(sdl, obj, tab, &dist , d);
		light = light->next;
	}
	return ((sdl->pref == 1 && tmp2->name != PLANE_ID) ? tab : reflection(sdl, tmp2, pos, tab));
}

float *calculate_light(t_sdl *sdl, t_object *obj, float *tab, t_light *light)
{
	t_vector pos; //вектор идущий из камеры в точку пересечения
	t_vector dist; // вектор из источника света в точку объекта
	float d;

	pos = (t_vector){sdl->cam.pos.x + sdl->t * sdl->ray_dir.x, sdl->cam.pos.y + sdl->t * sdl->ray_dir.y, sdl->cam.pos.z + sdl->t * sdl->ray_dir.z};
	sdl->norm = object_norm(sdl, obj, pos);
	while (light != NULL)
	{
		tab[3] = sdl->ambient; // фотновое освещение
		dist = vec_sub(&light->pos, &pos);
		d = ft_clamp((1.0 / sqrtf(sqrtf(vec_dot(&dist, &dist)))), 0.0, 1.0);
		dist = vec_norm(&dist);
		if (shadow(sdl, obj, light, pos) == 0)
			tab[3] += ft_clamp(vec_dot(&dist, &sdl->norm), 0.0, 1.0);
		tab = transfer_light(obj, light, tab, d);
		//printf("light.col = (%d %d %d)\n", light->col.r,light->col.g, light->col.b);
		//printf("tab[] = (%g %g %g %g)\n",tab[0], tab[1], tab[2], tab[3]);
		tab = gloss(sdl, obj, tab, &dist , d);
		//printf("tab[] = (%g %g %g %g)\n",tab[0], tab[1], tab[2], tab[3]);
		light = light->next;
	}
	sdl->refpos = (t_vector){sdl->ray_dir.x, sdl->ray_dir.y, sdl->ray_dir.z};
	return ((sdl->pref == 1 && obj->name != PLANE_ID) ? tab : reflection(sdl, obj, &pos, tab));
}
