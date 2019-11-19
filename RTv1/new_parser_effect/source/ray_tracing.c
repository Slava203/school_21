/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:38:16 by daron             #+#    #+#             */
/*   Updated: 2019/11/19 14:31:29 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

float	*ft_average(float *r, float *tab)
{
	r[0] += ft_clamp(tab[0], 0.0, 1.0);
	r[1] += ft_clamp(tab[1], 0.0, 1.0);
	r[2] += ft_clamp(tab[2], 0.0, 1.0);
	return (r);
}

void create_ray(t_sdl *sdl, double x, double y)
{
	double u;
	double v;

	u = (W_WIDTH - (double)x * 2.0) / W_HEIGHT;
	v = (W_HEIGHT - (double)y * 2.0) / W_WIDTH;
	//printf("(x, y) = (%g %g)\n", x, y);

	sdl->k = vec_sub(&sdl->cam.rot, &sdl->cam.pos);
	sdl->k = vec_norm(&sdl->k);
	//printf("k = (%g %g %g)\n", k.x, k.y, k.z);

	sdl->i = vec_cross(&sdl->k, &(t_vector){0.0, 1.0, 0.0});
	sdl->i = vec_norm(&sdl->i);
	//printf("i = (%g %g %g)\n", i.x, i.y, i.z);

	sdl->j = vec_cross(&sdl->i, &sdl->k);

	sdl->ray_dir = (t_vector){u * sdl->i.x + v * sdl->j.x + FOV * sdl->k.x, u * sdl->i.y + v * sdl->j.y + FOV * sdl->k.y, u * sdl->i.z + v * sdl->j.z + FOV * sdl->k.z};

	sdl->ray_dir = vec_norm(&sdl->ray_dir);
	sdl->cpt = 0;
	//printf("sdl->ray_dir = (%g, %g, %g)\n", sdl->ray_dir.x, sdl->ray_dir.y, sdl->ray_dir.z);
}

t_object *intersection(t_sdl *sdl, t_vector *ray_dir, t_vector *cam_pos)
{
	t_object *obj;
	double dist;
	t_object *head;

	obj = NULL;
	head = sdl->obj;
	sdl->t = 90000.0;
	while (head != NULL)
	{
		if (head->name == SPHERE_ID)
			dist = get_sphere_intersection(ray_dir, cam_pos, head, sdl);
		else if (head->name == CYLINDER_ID)
			dist = get_cylinder_intersection(ray_dir, cam_pos, head, sdl);
		else if (head->name == CONE_ID)
			dist = get_cone_intersection(ray_dir, cam_pos, head, sdl);
		else if (head->name == PLANE_ID)
			dist = get_plane_intersection(ray_dir, cam_pos, head, sdl);
		if (dist > EPS && dist < sdl->t)
		{
			obj = head;
			sdl->t = dist;
		}
		head = head->next;
	}
	return (obj);
}

void ft_tracing(double x, double y, double x_next, double y_next, t_sdl *sdl)
{
	float	*tab;
	float	r[3];
	t_object *obj;
	double p;

	if (!(tab = (float *)malloc(sizeof(float) * 4)))
		kill_all("Can't create tab <ft_tracing>");
	ft_fzero(r, 3);
	p = 0.0;
	while (y < y_next)
	{
		while (x < x_next)
		{
			p += 1;
			create_ray(sdl, x, y);
			ft_fzero(tab, 4);
			if((obj = intersection(sdl, &sdl->ray_dir, &sdl->cam.pos)))
				tab = calculate_light(sdl, obj, tab, sdl->light);
			//obj = intersection(sdl, &sdl->ray_dir, &sdl->cam.pos);
			//printf("(x, y) = (%d, %d) inter_point = %g tab[] = (%g %g %g)\n", (int)x, (int)y, sdl->t, tab[0], tab[1], tab[2]);
			ft_average(r, tab);
			x = x + (1.0 / sdl->dital);
		}
		y = y + (1.0 / sdl->dital);
	}
	//printf("(x, y) = (%d, %d) p = %g\n", (int)x - 1, (int)y - 1, p);
	SDL_SetRenderDrawColor(sdl->render, (int)(r[0] / p * 255) & 0xff, (int)(r[1] / p * 255) & 0xff, (int)(r[2] / p * 255) & 0xff, 255);

	/*SDL_SetRenderDrawColor(sdl->render, (((int)(r[0] / p * 255) & 0xff) << 16),
			(((int)(r[1] / p * 255) & 0xff) << 8),
			((int)(r[2] / p * 255) & 0xff), 255);*/
	/*printf("(x, y) = (%d, %d) pixel color = (%d %d %d)\n\n",(int)x - 1, (int)y - 1,  ((int)(r[0] / p * 255) & 0xff),
			((int)(r[1] / p * 255) & 0xff),
			((int)(r[2] / p * 255) & 0xff));*/

	SDL_RenderDrawPoint(sdl->render, (int)x - 1, (int)y - 1);
	free(tab);
}

void ray_tracing_init(t_sdl *sdl) // расчет направления луча идущего из камеры в заданный пиксель
{
	double x;
	double y;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			ft_tracing(x, y, x + 1, y + 1 ,sdl);
			x++;
		}
		y++;
	}
	SDL_RenderPresent(sdl->render);
}