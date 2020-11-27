/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:20:37 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 12:48:58 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>

# include "ftvector.h"
# include "libft.h"

# include <SDL2/SDL.h>

/*
** Size configuration
*/
# define W_WIDTH 	800
# define W_HEIGHT 	800

# define V_WIDTH 	40
# define V_HEIGHT 	40
/*
** Object name
*/
# define SPHERE "sphere:"
# define PLANE "plane:"
# define CYLINDER "cylinder:"
# define CONE "cone:"

# define CAMERA "cam:"

# define LIGHT "light:"

# define AMBIENT "ambient:"

/*
** Object id
*/
# define SPHERE_ID 1
# define PLANE_ID 2
# define CYLINDER_ID 3
# define CONE_ID 4

/*
** Help
*/
# define EPS 0.000001

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

typedef struct s_color
{
	int r;
	int g;
	int b;
}				t_color;

/*
** pos - Camera position
** rot - Camera rotation
*/
typedef	struct		s_cam
{
	t_vector		pos;
	t_vector		rot;
}					t_cam;

/*
** orig - Camera position - start of ray
** dir - direction of the ray
*/
typedef	struct		s_ray
{
	t_vector		orig;
	t_vector		dir;
}					t_ray;

/*
** n - normal for current object
** p - ray for the camera to view point
*/
typedef	struct		s_light
{
	t_vector		pos;
	double			inten;
	t_vector		p;
	t_vector		n;
	double			new_inten;
}					t_light;

/*
**  specular - зеркальность
*/
typedef struct		s_object
{
	t_vector		pos;
	t_vector		rot;
	t_color			col;
	double			r;
	double			t;
	int				name;
	double			specular;
}					t_object;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*render;
	t_cam			cam;
	t_object		*obj;
	t_light			*light;

	int				obj_num; // Количество объектов в сцене
	int				light_num; // Количество источников света

	int				obj_counter;
	int				light_counter;

	int				clos_obj;
	int				cam_is; // Существует ли камера
	double			min_t;
	double			ambient;
}					t_sdl;

/*
** It's help you - http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
*/

void scene_parser(t_sdl *sdl, char *scene_name);
int		kill_all(char *message);
void sdl_initialize(t_sdl *sdl);
double	get_quadratic_solution(double a, double b, double discriminant);

void free_mas(char **mas);

int	validate_line(char *line);
void object_count(char **param, t_sdl *sdl);
void validate_scene(char *scene_name, t_sdl *sdl);
int	validate_line(char *line);
void validation_param_count(char **str);
void param_validation(char **figure_name, int param_count);
int	validate_number(char *val_num);
void color_validation(t_color *color);

void object_parser(t_sdl *sdl, char **param);
void scene_parser(t_sdl *sdl, char *scene_name);

void init_camera(t_sdl *sdl, char **param);

void init_light(t_sdl *sdl, char **param);
void light(t_sdl *sdl, t_ray *ray);

void init_sphere(t_sdl *sdl, char **param);
void sphere_intersection(t_sdl *sdl, t_ray *camera, int i, t_object *obj);
t_vector get_sphere_normal(t_ray *ray, t_object *obj);
double get_sphere_intersection(t_vector cam_pos, t_vector dir, t_object *obj);

void init_plane(t_sdl *sdl, char **param);
void plane_intersection(t_sdl *sdl, t_ray *camera, int i, t_object *obj);
t_vector get_plane_normal(t_ray *ray, t_object *obj);
double get_plane_intersection(t_vector cam_pos, t_vector dir, t_object *obj);

void init_cylinder(t_sdl *sdl, char **param);
void cylinder_intersection(t_sdl *sdl, t_ray *camera, int i, t_object *obj);
t_vector get_cylinder_normal(t_ray *ray, t_object *obj);
double get_cylinder_intersection(t_vector cam_pos, t_vector dir, t_object *obj);

void init_cone(t_sdl *sdl, char **param);
void cone_intersection(t_sdl *sdl, t_ray *camera, int i, t_object *obj);
t_vector get_cone_normal(t_ray *ray, t_object *obj);
double get_cone_intersection(t_vector cam_pos, t_vector dir, t_object *obj);

void ray_tracing_init(t_sdl *sdl, t_ray *ray);
void get_direction(t_point point, t_ray *ray, t_sdl *sdl);

t_point init_point(double x, double y);

void init_ambient(t_sdl *sdl, char **param);

#endif