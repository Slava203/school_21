/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:46:59 by daron             #+#    #+#             */
/*   Updated: 2019/10/14 12:39:17 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_complex	set_shift(t_fractol *frct)
{
	return (init_complex(FT_ABS(frct->max.re - frct->min.re),
			FT_ABS(frct->max.im - frct->min.im)));
}

void				move_fractol(int key, t_fractol *frct)
{
	t_complex		shift;

	shift = set_shift(frct);
	if (key == ARROW_UP && frct->is_help == 1)
	{
		frct->max.im -= shift.im * 0.005;
		frct->min.im -= shift.im * 0.005;
	}
	else if (key == ARROW_DOWN && frct->is_help == 1)
	{
		frct->max.im += shift.im * 0.005;
		frct->min.im += shift.im * 0.005;
	}
	else if (key == ARROW_LEFT && frct->is_help == 1)
	{
		frct->max.re += shift.im * 0.005;
		frct->min.re += shift.im * 0.005;
	}
	else if (key == ARROW_RIGHT && frct->is_help == 1)
	{
		frct->max.re -= shift.im * 0.005;
		frct->min.re -= shift.im * 0.005;
	}
	if (frct->is_help == 1)
		main_draw(frct);
}

int					button_press(int key, t_fractol *fractol)
{
	if (key == KEYBOARD_ESC)
	{
		free_fractol(fractol);
		exit(0);
	}
	else if (key == ARROW_UP || key == ARROW_DOWN ||
	key == ARROW_LEFT || key == ARROW_RIGHT)
		move_fractol(key, fractol);
	else if (key == NUM_PAD_PLUS || key == NUM_PAD_MINUS)
		change_iteration_count(key, fractol);
	else if (key == KEYBOARD_ZVEZDA)
		change_color(key, fractol);
	else if (key == KEYBOARD_EQUALLY)
		change_julia_state(key, fractol);
	else if (key == KEYBOARD_H)
		get_help(key, fractol);
	return (0);
}
