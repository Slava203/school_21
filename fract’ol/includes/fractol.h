/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:02:51 by daron             #+#    #+#             */
/*   Updated: 2019/10/29 16:36:07 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

# define FROCTOL_COUNT 		5
# define THREADS_COUNT 		10

/*
 ** Collor
*/
# define MENU_COLOR 		0xFFFFF0
# define TEXT_COLOR 		0x000000
# define HELP_LABEL 		0xFFFFFF

/*
 ** Size configuration
*/
# define WIDTH 				1300
# define HEIGHT 			1300
# define MENU_WIDTH 		480

/*
 ** Button configuration
*/
# define ARROW_UP			126
# define ARROW_DOWN			125
# define ARROW_LEFT			123
# define ARROW_RIGHT		124

# define NUM_PAD_PLUS		69
# define NUM_PAD_MINUS		78
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define KEYBOARD_ZVEZDA	67
# define KEYBOARD_ESC		53
# define KEYBOARD_EQUALLY	81

# define KEYBOARD_H			4

typedef	struct		s_color
{
	int red;
	int green;
	int blue;
}					t_color;

typedef struct		s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef struct		s_image
{
	void			*image;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_image;

/*
 ** с - Комплексное число из формулы фрактала
 ** сompres_ratio - зависимость между пикселями экрана и комплексным числом
*/

typedef struct		s_fractol
{
	void			*mlx;
	void			*window;
	t_image			*image;
	int				iteration_count;
	t_complex		min;
	t_complex		max;
	t_complex		сompres_ratio;
	t_complex		c;
	t_complex		k;
	int				is_julia_fixed;
	int				start_line;
	int				end_line;
	int				color_shift;
	char			*fractol_name;
	int				(*formula)(struct s_fractol *fractol);
	int				is_help;
}					t_fractol;

typedef struct		s_formula
{
	char			*name;
	int				(*formula)(t_fractol *fractol);
}					t_formula;

int					iterate_mandelbrot(t_fractol *fractol);
int					iterate_julia(t_fractol *fractol);
int					iterate_mandelbar(t_fractol *fractol);
int					iterate_celtic_mandelbrot(t_fractol *fractol);
int					iterate_perpendicular_mandelbrot(t_fractol *fractol);

t_complex			init_complex(double re, double im);
void				print_usage(void);
void				create_fractol(int count, char **name_list);
int					kill_all(char *message);
t_fractol			*init_fractol(char *fractol_name, void *mlx);

void				main_draw(t_fractol *fractol);
t_color				get_color(int iter_count, t_fractol *frct);
void				put_pixel(int x, int y, t_fractol *frct, t_color color);
void				*draw_part_of_fractol(void *param);
void				change_julia_state(int key, t_fractol *frct);
void				print_help_menu(t_fractol *frct);

int					mouse_zoom(int button, int x, int y, t_fractol *frct);
int					julia_movement(int x, int y, t_fractol *frct);

void				print_help_menu(t_fractol *frct);
void				print_help_text(t_fractol *frct);

void				free_fractol(t_fractol *frcf);

int					button_press(int key, t_fractol *fractol);
void				move_fractol(int key, t_fractol *frct);
void				change_iteration_count(int key, t_fractol *frct);
void				change_color(int key, t_fractol *frct);
void				change_julia_state(int key, t_fractol *frct);
void				get_help(int key, t_fractol *frct);

#endif
