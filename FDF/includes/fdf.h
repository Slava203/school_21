/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:41:48 by daron             #+#    #+#             */
/*   Updated: 2019/10/09 15:21:09 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "libft.h"
# include "mlx.h"

/*
 ** Size configuration
*/
# define WIDTH 1700
# define HEIGHT 1200
# define MENU_WIDTH 250

/*
 ** Color configuration
*/
# define BACKGROUNG_MAIN 0x696969
# define BACKGROUNG_MENU 0x3f3f3f
# define FIGURE_START 0xFF4500
# define FIGURE_END 0x32CD32
# define TEXT_MENU 0xFFFFFF

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

# define KEYBOARD_Q			12
# define KEYBOARD_A			0
# define KEYBOARD_W			13
# define KEYBOARD_S			1
# define KEYBOARD_E			14
# define KEYBOARD_D			2

# define KEYBOARD_1			18
# define KEYBOARD_2			19
# define KEYBOARD_3			20
# define KEYBOARD_4			21

# define KEYBOARD_ESC		53

/*
 ** Structure definition
*/
typedef enum
{
	ISO,
	PARALLEL
}	t_projection;

typedef struct		s_camera
{
	t_projection	projection;
	double			zoom;
	double			alp;
	double			bet;
	double			gam;
	float			z_divisor;
	int				x_offset;
	int				y_offset;
}					t_camera;

typedef struct		s_map
{
	int				width;
	int				height;
	int				min;
	int				max;
	int				*z_coordinate;
	int				*collor_mas;
}					t_map;

typedef struct		s_fdf
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	t_map			*map;
	t_camera		*camera;
}					t_fdf;

typedef struct		s_coord
{
	int				z;
	int				color;
	struct s_coord	*next;
}					t_coord;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				collor;
}					t_point;

/*
 ** Function definition
*/
int					kill_pr(char *message);
t_coord				*new_coord(char *str);
void				reader(int fd, t_map *map, t_coord **head);
t_map				*new_map();
t_point				new_point(int x, int y, t_map *map);
void				push(t_coord **head, t_coord *new);
void				pars_string(t_map *map, t_coord **head, char **mas);
void				free_split_mas(char **mas);
t_coord				*pop(t_coord **head);
t_fdf				*new_fdf(t_map *map);
void				pars_stack(t_coord **head, t_map *map);
t_camera			*new_camera(t_fdf *fdf);
void				main_draw(t_fdf *tdf);
int					default_color(int x, t_map *map);
int					get_color(t_point current, t_point start,
		t_point end, t_point delta);
int					get_light(int p1, int p2, double percent);
int					default_color(int x, t_map *map);
t_point				project(t_point p, t_fdf *fdf);
void				button_pres(t_fdf *fdf);
int					close_window(void *str);
int					keyboard_press(int key, void *fdf);
void				zoom(int key, t_fdf *fdf);
void				move(int key, t_fdf *fdf);
void				rotate(int key, t_fdf *fdf);
void				rotate(int key, t_fdf *fdf);
void				change_projection(int key, t_fdf *fdf);
void				draw_menu(t_fdf *fdf);
void				free_fdf(t_fdf *fdf);

#endif
