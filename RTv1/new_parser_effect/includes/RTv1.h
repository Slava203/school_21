/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:20:37 by daron             #+#    #+#             */
/*   Updated: 2019/11/21 16:58:32 by daron            ###   ########.fr       */
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
# define W_WIDTH		800
# define W_HEIGHT		800
# define FOV			2.0
# define EPS			0.0001
# define ALPHA			0.05
# define DELTA			10.0
/*
** Object id
*/
# define SPHERE_ID		1
# define PLANE_ID		2
# define CYLINDER_ID	3
# define CONE_ID		4
/*
** Help
*/

# define SEKKS			sdl->event.key.keysym.sym
# define SSO			sdl->select_obj
# define SC				sdl->cam

typedef struct		s_move
{
	t_vector		i;
	t_vector		j;
	t_vector		k;
}					t_move;

typedef struct		s_color
{
	float			r;
	float			g;
	float			b;
}					t_color;

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
	float			specular;
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
	double			ambient; //освещенность
	int				line_count; // количество линий в buf
	char			**scene; //храним сцену джля парсинга
	int 			dital; //дитализация =  количество проходов при построение изображения
	t_vector		ray_dir; // луч отправленный из камеры в сцену
	double			t;
	t_vector		norm;
	float			t0;
	t_vector 		dist;
	int				gloss_activ;
	int 			cpt;
	int				reflect_count;
	t_vector		refpos;
	t_vector		ref;
	int 			pref;
	t_vector 		i;
	t_vector 		j;
	t_vector 		k;
	t_object		*select_obj;

}					t_sdl;

/*
** It's help you - http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
*/

void scene_parser(t_sdl *sdl, char *scene_name);
int		kill_all(char *message);
void sdl_initialize(t_sdl *sdl);
double	get_quadratic_solution(double a, double b, double discriminant);

void free_mas(char **mas);
void my_free(t_sdl *sdl);
float   ft_clamp(float value, float min, float max);

void object_parser(t_sdl *sdl, char **param);
void scene_parser(t_sdl *sdl, char *scene_name);

void ray_tracing_init(t_sdl *sdl);
t_object *intersection(t_sdl *sdl, t_vector *ray_dir, t_vector *cam_pos);
double get_sphere_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl);
double get_cylinder_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl);
double get_cone_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl);
double get_plane_intersection(t_vector *ray_dir, t_vector *cam_pos, t_object *obj, t_sdl *sdl);

void			init_ambient(t_sdl *sdl, char **param);
void			string_parser(t_sdl *sdl);

int				ft_atoi_n(char *str, int *k);
t_light			*ft_add_light_link(t_sdl *sdl, t_light *link);
t_object		*ft_add_object_link(t_sdl *sdl, t_object *link);

void			ft_add_light(t_sdl *sdl, int *k, int ind);
void			ft_add_cyl_cone(t_sdl *sdl, int *k, int name, int ind);
void			ft_add_plane(t_sdl *sdl, int *k, int i);
void			ft_add_sphere(t_sdl *sdl, int *k, int i);
void			check_object(t_sdl *sdl);
void			ft_col_n_pos(t_sdl *sdl, t_object *link, int k);

float			*calculate_light(t_sdl *sdl, t_object *obj, float *tab, t_light *light);
t_vector		object_norm(t_sdl *sdl, t_object *obj, t_vector pos);
float			*transfer_light(t_object *obj, t_light *light, float *tab, float d);
float			*gloss(t_sdl *sdl, t_object *obj, float *tab, t_vector *dist, float d);

void			events(t_sdl *sdl);
void			mouse_down(t_sdl *sdl);
void			key_down(t_sdl *sdl, t_move *move);
void			key_down_for_object(t_sdl *sdl, t_move *move);
void			detail_key(t_sdl *sdl);
void			swithc_gloss(t_sdl *sdl);
void			reflection_key(t_sdl *sdl);
void			swithc_pref(t_sdl *sdl);

#endif