/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 18:15:14 by daron             #+#    #+#             */
/*   Updated: 2019/10/08 13:51:36 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	rotate_x(int *y, int *z, double alpha)
{
	int		prev_y;

	prev_y = *y;
	*y = prev_y * cos(alpha) + *z * sin(alpha);
	*z = -prev_y * sin(alpha) + *z * cos(alpha);
}

static void	rotate_y(int *x, int *z, double alpha)
{
	int		prev_x;

	prev_x = *x;
	*x = prev_x * cos(alpha) + *z * sin(alpha);
	*z = -prev_x * sin(alpha) + *z * cos(alpha);
}

static void	rotate_z(int *x, int *y, double alpha)
{
	int		prev_x;
	int		prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(alpha) - prev_y * sin(alpha);
	*y = prev_x * sin(alpha) + prev_y * cos(alpha);
}

static void	iso(int *x, int *y, int z)
{
	int		prev_x;
	int		prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

t_point		project(t_point p, t_fdf *fdf)
{
	p.x *= fdf->camera->zoom;
	p.y *= fdf->camera->zoom;
	p.z *= fdf->camera->zoom / fdf->camera->z_divisor;
	p.x -= (fdf->map->width * fdf->camera->zoom) / 2;
	p.y -= (fdf->map->height * fdf->camera->zoom) / 2;
	rotate_x(&p.y, &p.z, fdf->camera->alp);
	rotate_y(&p.x, &p.z, fdf->camera->bet);
	rotate_z(&p.x, &p.y, fdf->camera->gam);
	if (fdf->camera->projection == ISO)
		iso(&p.x, &p.y, p.z);
	p.x += (WIDTH - MENU_WIDTH) / 2 + fdf->camera->x_offset + MENU_WIDTH;
	p.y += (HEIGHT + fdf->map->height * fdf->camera->zoom) / 2 +
			fdf->camera->y_offset;
	return (p);
}
