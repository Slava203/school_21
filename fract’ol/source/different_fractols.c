/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Different_fractols.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:55:58 by daron             #+#    #+#             */
/*   Updated: 2019/10/14 13:02:37 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		iterate_mandelbrot(t_fractol *fractol)
{
	int			iteration;
	t_complex	z;

	iteration = 0;
	z = init_complex(fractol->c.re, fractol->c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
	&& iteration < fractol->iteration_count)
	{
		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0)
				+ fractol->c.re, 2.0 * z.re * z.im + fractol->c.im);
		iteration++;
	}
	return (iteration);
}

int		iterate_julia(t_fractol *fractol)
{
	int			iteration;
	t_complex	z;

	iteration = 0;
	z = init_complex(fractol->c.re, fractol->c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
	&& iteration < fractol->iteration_count)
	{
		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0)
				+ fractol->k.re, 2.0 * z.re * z.im + fractol->k.im);
		iteration++;
	}
	return (iteration);
}

int		iterate_mandelbar(t_fractol *fractol)
{
	int			iteration;
	t_complex	z;

	iteration = 0;
	z = init_complex(fractol->c.re, fractol->c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
	&& iteration < fractol->iteration_count)
	{
		z = init_complex(pow(z.re, 2.0) - pow(z.im, 2.0)
				+ fractol->c.re, -2.0 * z.re * z.im + fractol->c.im);
		iteration++;
	}
	return (iteration);
}

int		iterate_celtic_mandelbrot(t_fractol *fractol)
{
	int			iteration;
	t_complex	z;

	iteration = 0;
	z = init_complex(fractol->c.re, fractol->c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
	&& iteration < fractol->iteration_count)
	{
		z = init_complex(fabs(pow(z.re, 2.0) - pow(z.im, 2.0))
				+ fractol->c.re, 2.0 * z.re * z.im + fractol->c.im);
		iteration++;
	}
	return (iteration);
}

int		iterate_perpendicular_mandelbrot(t_fractol *fractol)
{
	int			iteration;
	t_complex	z;

	iteration = 0;
	z = init_complex(fractol->c.re, fractol->c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
	&& iteration < fractol->iteration_count)
	{
		z = init_complex(
				pow(z.re, 2.0) - pow(z.im, 2.0) + fractol->c.re,
				-2.0 * fabs(z.re) * z.im + fractol->c.im);
		iteration++;
	}
	return (iteration);
}
