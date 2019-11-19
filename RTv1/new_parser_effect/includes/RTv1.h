/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:20:37 by daron             #+#    #+#             */
/*   Updated: 2019/11/19 16:43:48 by daron            ###   ########.fr       */
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

# define FOV 2.0
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
# define EPS 0.0001

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

typedef struct s_color
{
	float r;
	float g;
	float b;
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
	t_color			col;

	t_vector		p;
	t_vector		n;

	double			new_inten;

	struct s_light	*next;
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
	int				name;

	double			specular;

	double			t;

	struct s_object	*next;
}					t_object;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*render;
	SDL_Event		event;
	t_cam			cam;
	t_object		*obj;
	t_light			*light;

	int				obj_num; // Количество объектов в сцене
	int				light_num; // Количество источников света

	int				obj_counter;
	int				light_counter;

	t_object		*clos_obj;
	int				cam_is; // Существует ли камера
	double			min_t;

	double			ambient; //освещенность

	int				line_count; // количество линий в buf
	char			**scene; //храним сцену джля парсинга

	int 			dital; //дитализация =  количество проходов при построение изображения

	t_vector		ray_dir; // луч отправленный из камеры в сцену
	double			t;
	t_vector		norm;
	float			t0;
	t_vector 		dist;

	float			a;
	int				gloss_activ;

	int 			cpt;
	int				reflect_count;

	t_vector		refpos;
	t_vector		ref;

	int 			pref;

	t_vector 			i;
	t_vector 			j;
	t_vector 			k;

}					t_sdl;

/*
** It's help you - http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
*/

void scene_parser(t_sdl *sdl, char *scene_name);
int		kill_all(char *message);
void sdl_initialize(t_sdl *sdl);
double	get_quadratic_solution(double a, double b, double discriminant);

void free_mas(char **mas);
float   ft_clamp(float value, float min, float max);

void object_parser(t_sdl *sdl, char **param);
void scene_parser(t_sdl *sdl, char *scene_name);

void init_camera(t_sdl *sdl, char **param);

void light(t_sdl *sdl, t_ray *ray);

void ray_tracing_init(t_sdl *sdl);

double get_sphere_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl);
double get_cylinder_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl);
double get_cone_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl);
double get_plane_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl);


t_point init_point(double x, double y);

void init_ambient(t_sdl *sdl, char **param);

void string_parser(t_sdl *sdl);

int				ft_atoi_n(char *str, int *k);
t_light			*ft_add_light_link(t_sdl *sdl, t_light *link);
t_object		*ft_add_object_link(t_sdl *sdl, t_object *link);

void ft_col_n_pos(t_sdl *sdl, t_object *link, int k);

void	ft_add_light(t_sdl *sdl, int *k, int ind);
void	ft_add_cyl_cone(t_sdl *sdl, int *k, int name, int ind);
void	ft_add_plane(t_sdl *sdl, int *k, int i);
void	ft_add_sphere(t_sdl *sdl, int *k, int i);

void check_object(t_sdl *sdl);

float *calculate_light(t_sdl *sdl, t_object *obj, float *tab, t_light *light);
t_vector object_norm(t_sdl *sdl, t_object *obj, t_vector pos);
float *transfer_light(t_object *obj, t_light *light, float *tab, float d);
float *gloss(t_sdl *sdl, t_object *obj, float *tab, t_vector *dist, float d);

void	events(t_sdl *sdl);
void move_key(t_sdl *sdl);
void rotate_key(t_sdl *sdl);

#endif