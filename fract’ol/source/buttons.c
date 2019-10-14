/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:15:45 by daron             #+#    #+#             */
/*   Updated: 2019/10/14 12:02:40 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			change_iteration_count(int key, t_fractol *frct)
{
	if (frct->is_help == 1)
	{
		if (key == NUM_PAD_PLUS && frct->iteration_count < 3500)
		{
			if (frct->iteration_count <= 100)
				frct->iteration_count += 1;
			else
				frct->iteration_count = (int)(frct->iteration_count * 1.05);
		}
		else if (key == NUM_PAD_MINUS && frct->iteration_count > 0)
		{
			if (frct->iteration_count > 100)
				frct->iteration_count = (int)(frct->iteration_count * 0.95);
			else
				frct->iteration_count -= 1;
		}
		main_draw(frct);
	}
}

void			change_color(int key, t_fractol *frct)
{
	if (key == KEYBOARD_ZVEZDA && frct->is_help == 1)
	{
		frct->color_shift = (frct->color_shift + 1) % 3;
		main_draw(frct);
	}
}

void			change_julia_state(int key, t_fractol *frct)
{
	if (key == KEYBOARD_EQUALLY && frct->is_help == 1)
		frct->is_julia_fixed = !frct->is_julia_fixed;
}

void			get_help(int key, t_fractol *frct)
{
	if (key == KEYBOARD_H)
		frct->is_help = !frct->is_help;
	main_draw(frct);
}
