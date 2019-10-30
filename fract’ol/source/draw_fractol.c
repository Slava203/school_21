/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:36:51 by daron             #+#    #+#             */
/*   Updated: 2019/10/29 16:36:07 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color			get_color(int iter_count, t_fractol *frct)
{
	int			color_mas[3];
	t_color		color;
	double		cur_place;

	cur_place = (double)iter_count / frct->iteration_count;
	color_mas[0] = (int)(9 * (1 - cur_place) * ft_pow(cur_place, 3) * 255);
	color_mas[1] = (int)(15 * ft_pow((1 - cur_place), 2) * ft_pow(cur_place, 2)
			* 100);
	color_mas[2] = (int)(8.5 * ft_pow((1 - cur_place), 3) * cur_place * 255);
	color.red = color_mas[(0 + frct->color_shift) % 3];
	color.green = color_mas[(1 + frct->color_shift) % 3];
	color.blue = color_mas[(2 + frct->color_shift) % 3];
	return (color);
}

void			put_pixel(int x, int y, t_fractol *frct, t_color color)
{
	int			ind;

	ind = (x * frct->image->bits_per_pixel / 8) + (y * frct->image->size_line);
	frct->image->data_addr[ind] = color.blue;
	frct->image->data_addr[++ind] = color.green;
	frct->image->data_addr[++ind] = color.red;
	frct->image->data_addr[++ind] = 0;
}

void			*draw_part_of_fractol(void *param)
{
	int			x;
	int			y;
	t_fractol	*frct;

	frct = (t_fractol*)param;
	y = frct->start_line;
	while (y < frct->end_line)
	{
		frct->c.im = frct->max.im - y * frct->сompres_ratio.im;
		x = 0;
		while (x < WIDTH)
		{
			frct->c.re = frct->min.re + x * frct->сompres_ratio.re;
			put_pixel(x, y, frct, get_color(frct->formula(frct), frct));
			x++;
		}
		y++;
	}
	return (0);
}

void			print_help_menu(t_fractol *frct)
{
	int			i;
	int			j;
	int			ind;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < MENU_WIDTH)
		{
			ind = (j * frct->image->bits_per_pixel / 8) +
					(i * frct->image->size_line);
			frct->image->data_addr[ind] = (char)255;
			frct->image->data_addr[++ind] = (char)255;
			frct->image->data_addr[++ind] = (char)255;
			frct->image->data_addr[++ind] = (char)100;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(frct->mlx, frct->window, frct->image->image, 0, 0);
	print_help_text(frct);
}
