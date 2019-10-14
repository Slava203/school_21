/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:02:22 by daron             #+#    #+#             */
/*   Updated: 2019/10/14 12:02:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex		init_complex(double re, double im)
{
	t_complex	number;

	number.re = re;
	number.im = im;
	return (number);
}

int				kill_all(char *message)
{
	perror(message);
	exit(1);
}

void			print_usage(void)
{
	ft_putstr("usage: fractol fractol_name_1 .. fractol_name_n\n");
	ft_putstr("       Types of fractals supported in the program:\n");
	ft_putstr("        - Mandelbrot\n");
	ft_putstr("        - Julia\n");
	ft_putstr("        - Mandelbar\n");
	ft_putstr("        - Celtic Mandelbrot\n");
	ft_putstr("        - Perpendicular Mandelbrot\n");
}

void			free_fractol(t_fractol *frcf)
{
	free(frcf->image->image);
	free(frcf->image->data_addr);
	free(frcf->mlx);
	free(frcf->window);
	free(frcf->image);
	free(frcf);
}
