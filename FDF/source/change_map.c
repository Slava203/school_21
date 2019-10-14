/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:36:30 by daron             #+#    #+#             */
/*   Updated: 2019/10/02 17:36:44 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		zoom(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_PLUS)
		fdf->camera->zoom += 0.2;
	else if (key == NUM_PAD_MINUS && fdf->camera->zoom > 1)
		fdf->camera->zoom -= 0.2;
	main_draw(fdf);
}

void		move(int key, t_fdf *fdf)
{
	if (key == ARROW_RIGHT)
		fdf->camera->x_offset += 3;
	else if (key == ARROW_LEFT)
		fdf->camera->x_offset -= 3;
	else if (key == ARROW_UP)
		fdf->camera->y_offset -= 3;
	else if (key == ARROW_DOWN)
		fdf->camera->y_offset += 3;
	main_draw(fdf);
}

void		rotate(int key, t_fdf *fdf)
{
	double	alpfa;

	alpfa = 0.05;
	if (key == KEYBOARD_Q)
		fdf->camera->alp += alpfa;
	else if (key == KEYBOARD_A)
		fdf->camera->alp -= alpfa;
	else if (key == KEYBOARD_W)
		fdf->camera->bet += alpfa;
	else if (key == KEYBOARD_S)
		fdf->camera->bet -= alpfa;
	else if (key == KEYBOARD_E)
		fdf->camera->gam += alpfa;
	else if (key == KEYBOARD_D)
		fdf->camera->gam -= alpfa;
	main_draw(fdf);
}

void		change_projection(int key, t_fdf *fdf)
{
	fdf->camera->alp = 0;
	fdf->camera->bet = 0;
	fdf->camera->gam = 0;
	if (key == KEYBOARD_1)
		fdf->camera->projection = ISO;
	else if (key == KEYBOARD_2)
		fdf->camera->projection = PARALLEL;
	else if (key == KEYBOARD_3)
	{
		fdf->camera->projection = PARALLEL;
		fdf->camera->alp = -1.5708;
		fdf->camera->bet = 1.5708;
	}
	else if (key == KEYBOARD_4)
	{
		fdf->camera->projection = PARALLEL;
		fdf->camera->alp = -1.5708;
	}
	main_draw(fdf);
}
