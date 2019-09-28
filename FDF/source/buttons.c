/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:29:17 by daron             #+#    #+#             */
/*   Updated: 2019/09/26 19:03:12 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(void *str)
{
	(void)str;
	exit(0);
}

int keyboard_press(int key, void *param)
{
	t_fdf	*fdf;
	fdf = (t_fdf *)param;
	if (key == KEYBOARD_ESC)
		exit(0);
	else if (key == NUM_PAD_PLUS || key == NUM_PAD_MINUS || key == MOUSE_SCROLL_UP || key == MOUSE_SCROLL_DOWN)
		zoom(key, fdf);
	else if (key == ARROW_RIGHT || key == ARROW_LEFT || key == ARROW_UP || key == ARROW_DOWN)
		move(key, fdf);
	else if (key == KEYBOARD_Q || key == KEYBOARD_A || key == KEYBOARD_W || key == KEYBOARD_S || key == KEYBOARD_E || key == KEYBOARD_D)
		rotate(key, fdf);
		return (0);
}

void button_pres(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 0, keyboard_press, fdf);
}