/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:43:57 by daron             #+#    #+#             */
/*   Updated: 2019/09/26 14:25:05 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void print_pixel(t_fdf *fdf, int x, int y, int color)
{
	int ind;

	if (x >= MENU_WIDTH && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		ind = ((x * fdf->bits_per_pixel / 8) + (y * fdf->size_line));
		fdf->data_addr[ind] = color;
		ind++;
		fdf->data_addr[ind] = color >> 8;
		ind++;
		fdf->data_addr[ind] = color >> 16;
	}
}

static void draw_line(t_point p1, t_point p2, t_fdf *fdf)
{
	t_point	delta;
	t_point	sign;
	t_point	cur_point;
	int		error[2];

	delta.x = FT_ABS(p2.x - p1.x);
	delta.y = FT_ABS(p2.y - p1.y);
	sign.x = p1.x < p2.x ? 1 : -1;
	sign.y = p1.y < p2.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur_point = p1;
	while (cur_point.x != p2.x || cur_point.y != p2.y)
	{
		print_pixel(fdf, cur_point.x, cur_point.y, get_color(cur_point, p1, p2, delta));
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur_point.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur_point.y += sign.y;
		}
	}
}

static void draw_background(t_fdf *fdf)
{
	int *image;
	size_t i;
	size_t size;

	size = WIDTH * HEIGHT;
	ft_bzero(fdf->data_addr, size * (fdf->bits_per_pixel / 8));
	image = (int*)(fdf->data_addr);
	i = 0;
	while (i < size)
	{
		if (i % WIDTH < MENU_WIDTH)
			image[i] = BACKGROUNG_MENU;
		else
			image[i] = BACKGROUNG_MAIN;
		i++;
	}
}

void main_draw(t_fdf *fdf)
{
	int x;
	int y;

	draw_background(fdf);
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x != fdf->map->width - 1)
				draw_line(project(new_point(x, y, fdf->map), fdf), project(new_point(x + 1, y, fdf->map), fdf), fdf);
			if (y != fdf->map->height - 1)
				draw_line(project(new_point(x, y, fdf->map), fdf), project(new_point(x, y + 1, fdf->map), fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

