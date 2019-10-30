/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:17:05 by daron             #+#    #+#             */
/*   Updated: 2019/10/29 16:36:07 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	progection(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int				mouse_zoom(int button, int x, int y, t_fractol *frct)
{
	t_complex	shift;
	double		zoom;
	double		percent;

	if ((button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	&& frct->is_help == 1)
	{
		shift = init_complex((double)x / (WIDTH / (frct->max.re -
				frct->min.re)) + frct->min.re, (double)y / (HEIGHT /
				(frct->max.im - frct->min.im)) * -1 + frct->max.im);
		if (button == MOUSE_SCROLL_UP)
			zoom = 0.60;
		else
			zoom = 1.10;
		percent = 1.0 / zoom;
		frct->min.re = progection(shift.re, frct->min.re, percent);
		frct->min.im = progection(shift.im, frct->min.im, percent);
		frct->max.re = progection(shift.re, frct->max.re, percent);
		frct->max.im = progection(shift.im, frct->max.im, percent);
		main_draw(frct);
	}
	return (0);
}

int				julia_movement(int x, int y, t_fractol *frct)
{
	if (!frct->is_julia_fixed && frct->is_help == 1)
	{
		frct->k = init_complex(4 * ((double)x / WIDTH - 0.5),
				4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		main_draw(frct);
	}
	return (0);
}
