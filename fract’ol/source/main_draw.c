/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:07:54 by daron             #+#    #+#             */
/*   Updated: 2019/10/13 15:29:02 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		help_draw(t_fractol *frct)
{
	if (!frct->is_help)
		print_help_menu(frct);
	else
		mlx_put_image_to_window(frct->mlx, frct->window,
								frct->image->image, 0, 0);
	mlx_string_put(frct->mlx, frct->window,
			WIDTH - 200, 30, HELP_LABEL, "\"H\" is help you");
}

void			main_draw(t_fractol *frct)
{
	pthread_t	threads_id[THREADS_COUNT];
	t_fractol	frac_mas[THREADS_COUNT];
	int			ind;

	ind = 0;
	frct->сompres_ratio = init_complex((frct->max.re - frct->min.re) /
			(WIDTH - 1), (frct->max.im - frct->min.im) / (HEIGHT - 1));
	while (ind < THREADS_COUNT)
	{
		frac_mas[ind] = *frct;
		frac_mas[ind].start_line = ind * (HEIGHT / THREADS_COUNT);
		frac_mas[ind].end_line = (ind + 1) * (HEIGHT / THREADS_COUNT);
		if (pthread_create(&threads_id[ind], NULL, draw_part_of_fractol,
				(void*)&frac_mas[ind]))
			kill_all("Can't initialize pthread <main_draw>");
		ind++;
	}
	while (ind-- > 0)
	{
		if (pthread_join(threads_id[ind], NULL))
			kill_all("Can't join the pthread <main_draw>");
	}
	help_draw(frct);
}
