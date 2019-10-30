/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:55:52 by daron             #+#    #+#             */
/*   Updated: 2019/10/29 16:36:07 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int						(*detect_fotmula(char *frct_name)) (t_fractol *fractol)
{
	size_t				ind;
	int					(*formula)(t_fractol *fract);
	static t_formula	list[] = {
			{ "Mandelbrot", &iterate_mandelbrot },
			{ "Julia", &iterate_julia },
			{ "Mandelbar", &iterate_mandelbar},
			{ "Celtic Mandelbrot", &iterate_celtic_mandelbrot},
			{ "Perpendicular Mandelbrot", &iterate_perpendicular_mandelbrot}
	};

	ind = 0;
	formula = NULL;
	while (ind < sizeof(list) / sizeof(t_formula))
	{
		if (ft_strequ(list[ind].name, frct_name))
		{
			formula = list[ind].formula;
			break ;
		}
		ind++;
	}
	return (formula);
}

static void				set_start_parametrs(t_fractol *ptr)
{
	ptr->iteration_count = 50;
	ptr->min = init_complex(-2.0, -2.0);
	ptr->max.re = 2.0;
	ptr->max.im = ptr->min.im + (ptr->max.re - ptr->min.re) * HEIGHT / WIDTH;
	ptr->k = init_complex(-0.4, 0.6);
	ptr->color_shift = 0;
	ptr->is_julia_fixed = 1;
	ptr->is_help = 1;
}

t_fractol				*init_fractol(char *fractol_name, void *mlx)
{
	t_fractol	*ptr;

	if (!(ptr = (t_fractol*)malloc(sizeof(t_fractol))))
		kill_all("Can't create fractol <init_fractol>");
	ptr->mlx = mlx;
	if (!(ptr->window = mlx_new_window(ptr->mlx, WIDTH, HEIGHT, fractol_name)))
		kill_all("Can't create window <init_fractol>");
	ptr->fractol_name = fractol_name;
	if (!(ptr->image = (t_image*)malloc(sizeof(t_image))))
		kill_all("Can't create image <init_fractol>");
	if (!(ptr->image->image = mlx_new_image(mlx, WIDTH, HEIGHT)))
		kill_all("Can't execute mlx_new_image <init_fractol>");
	ptr->image->data_addr = mlx_get_data_addr(ptr->image->image,
			&(ptr->image->bits_per_pixel), &(ptr->image->size_line),
			&(ptr->image->endian));
	if (!(ptr->formula = detect_fotmula(fractol_name)))
		kill_all("Can't detect formula <init_fractol>");
	set_start_parametrs(ptr);
	mlx_hook(ptr->window, 2, 0, button_press, ptr);
	mlx_hook(ptr->window, 4, 0, mouse_zoom, ptr);
	if (ft_strequ(fractol_name, "Julia"))
		mlx_hook(ptr->window, 6, 0, julia_movement, ptr);
	return (ptr);
}

void					create_fractol(int count, char **name_list)
{
	t_fractol	*list[FROCTOL_COUNT];
	int			ind;
	void		*mlx;

	ind = 0;
	if (!(mlx = mlx_init()))
		kill_all("Can't create mlx <init_fractol>");
	while (ind < count)
	{
		list[ind] = init_fractol(name_list[ind], mlx);
		main_draw(list[ind]);
		ind++;
	}
	mlx_loop(mlx);
}

int						main(int argc, char **argv)
{
	int			ind;

	if (argc >= 2 && argc <= 5)
	{
		ind = 1;
		while (ind <= argc)
		{
			if (!detect_fotmula(argv[ind]))
				break ;
			ind++;
		}
		if (ind == argc)
			create_fractol(ind - 1, &argv[1]);
		else
			print_usage();
	}
	else
		print_usage();
	return (0);
}
