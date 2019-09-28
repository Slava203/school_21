/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:36:30 by daron             #+#    #+#             */
/*   Updated: 2019/09/26 19:35:06 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void zoom(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_PLUS)
		fdf->camera->zoom++;
	else if (key == NUM_PAD_MINUS)
		fdf->camera->zoom--;
	main_draw(fdf);
}

void move(int key, t_fdf *fdf)
{
	if (key == ARROW_RIGHT)
		fdf->camera->x_offset += 3;
	else if (key == ARROW_LEFT)
		fdf->camera->x_offset -= 3;
	else if (key == ARROW_UP)
		fdf->camera->y_offset -= 3;
	else if (key == ARROW_DOWN)
		fdf->camera->y_offset +=3;
	main_draw(fdf);
}

void rotate(int key, t_fdf *fdf)
{
	double alpfa;

	alpfa = 0.1;
	if(key == KEYBOARD_Q)
		fdf->camera->alp +=alpfa;
	else if (key == KEYBOARD_A)
		fdf->camera->alp -=alpfa;
	else if (key == KEYBOARD_W)
		fdf->camera->bet +=alpfa;
	else if (key == KEYBOARD_S)
		fdf->camera->bet -=alpfa;
	else if (key == KEYBOARD_E)
		fdf->camera->gam +=alpfa;
	else if (key == KEYBOARD_D)
		fdf->camera->gam -=alpfa;
	main_draw(fdf);
}