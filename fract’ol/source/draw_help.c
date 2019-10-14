/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:42:07 by daron             #+#    #+#             */
/*   Updated: 2019/10/13 15:42:49 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		print_help_text_1(t_fractol *f, int offset, int i)
{
	void		*win;

	win = f->window;
	if (ft_strequ(f->fractol_name, "Julia"))
	{
		mlx_string_put(f->mlx, win, offset + 10, i += 30, TEXT_COLOR,
				"For the Julia:");
		mlx_string_put(f->mlx, win, offset + 35, i += 20, TEXT_COLOR,
				"you can unfix fractol use \"=\"");
		mlx_string_put(f->mlx, win, offset + 35, i += 20, TEXT_COLOR,
				"and move shape using mouse");
	}
	mlx_string_put(f->mlx, win, offset + 10, i += 30, TEXT_COLOR,
			"DARON'S PROGECT:)");
}

void			print_help_text(t_fractol *f)
{
	int			i;
	int			offset;
	void		*win;

	i = 15;
	offset = 22;
	win = f->window;
	mlx_string_put(f->mlx, win, offset, i += 15, TEXT_COLOR, "BUTTON MENU:");
	mlx_string_put(f->mlx, win, offset + 10, i += 15, TEXT_COLOR, "1) Move:");
	mlx_string_put(f->mlx, win, offset + 35, i += 20, TEXT_COLOR,
			"- Use arrows");
	mlx_string_put(f->mlx, win, offset + 10, i += 15, TEXT_COLOR,
			"2) Change color:");
	mlx_string_put(f->mlx, win, offset + 35, i += 20, TEXT_COLOR, "- +/-, *");
	mlx_string_put(f->mlx, win, offset + 10, i += 15, TEXT_COLOR,
			"3) ESC to close program");
	print_help_text_1(f, offset, i);
}
