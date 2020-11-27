/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:55:27 by daron             #+#    #+#             */
/*   Updated: 2019/10/22 16:01:34 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	validate_number(char *val_num)
{
	int	i;

	if (val_num[0] == '-' || val_num[0] == '+')
		i = 1;
	else
		i = 0;
	while (val_num[i])
	{
		if (ft_isdigit(val_num[i]) == 1)
			i++;
		else
			kill_all("Input is not number <validate_number>");
	}
	return (1);
}

void color_validation(t_color *color)
{
	if (!(color->r >= 0 && color->r <= 255) ||
		!(color->g >= 0 && color->g <= 255) ||
		!(color->b >= 0 && color->b <= 255))
		kill_all("Mistake in color <color_validation>");
}

void param_validation(char **param, int param_count)
{
	int ind;

	ind = 1;
	while (ind <= param_count)
	{
		if (!param[ind] || (ft_atoi(param[ind]) == 0 && param[ind][0] != '0') ||
				param[param_count + 1] != NULL  || !validate_number(param[ind]))
			kill_all("Mistake in figure parameters <param_validation>");
		ind++;
	}
}

void	validation_param_count(char **str)
{
	int i;

	i = 0;
	if (ft_strequ(str[0], CAMERA))
		param_validation(str, 6);
	else if (ft_strequ(str[0], SPHERE))
		param_validation(str, 8);
	else if (ft_strequ(str[0], PLANE))
		param_validation(str, 10);
	else if (ft_strequ(str[0], CYLINDER))
		param_validation(str, 11);
	else if (ft_strequ(str[0], CONE))
		param_validation(str, 11);
	else if (ft_strequ(str[0], LIGHT))
		param_validation(str, 4);
	else if (ft_strequ(str[0], AMBIENT))
		param_validation(str, 1);
}

int		validate_line(char *line)
{
	if (ft_strncmp(CAMERA, line, 4) == 0)
		return (1);
	if (ft_strncmp(LIGHT, line, 6) == 0)
		return (1);
	if (ft_strncmp(SPHERE, line, 7) == 0)
		return (1);
	if (ft_strncmp(CONE, line, 5) == 0)
		return (1);
	if (ft_strncmp(CYLINDER, line, 9) == 0)
		return (1);
	if (ft_strncmp(PLANE, line, 6) == 0)
		return (1);
	if (ft_strncmp(AMBIENT, line, 8) == 0)
		return (1);
	return (0);
}

void object_count(char **param, t_sdl *sdl)
{
	if (ft_strequ(param[0], SPHERE) || ft_strequ(param[0], PLANE) ||
		ft_strequ(param[0], CYLINDER) || ft_strequ(param[0], CONE))
		sdl->obj_num++;
	else if (ft_strequ(param[0], LIGHT))
		sdl->light_num++;
	else if (ft_strequ(param[0], CAMERA))
		sdl->cam_is++;
}

void free_mas(char **mas)
{
	int ind;

	ind = 0;
	while (mas[ind])
	{
		free(mas[ind]);
		ind++;
	}
	free(mas[ind]);
	free(mas);
}

void validate_scene(char *scene_name, t_sdl *sdl)
{
	int fd;
	char *line;
	char **param;

	if (!(fd = open(scene_name, O_RDWR)))
		kill_all("Can't open file <validate_scene>");
	while (get_next_line(fd, &line) > 0)
	{
		if (!validate_line(line))
			kill_all("Scene have forbiden object <validate_scene>");
		param = ft_strsplit(line, ' ');
		ft_strdel(&line);
		object_count(param, sdl);
		validation_param_count(param);
		free_mas(param);
	}
	if (sdl->cam_is != 1)
		kill_all("Please create camera <validate_scene>");
	if (sdl->light_num == 0)
		kill_all("Please create light <validate_scene>");
	if (sdl->obj_num == 0)
		kill_all("Please create object in scene <validate_scene>");
	close(fd);
}
//----------------------------------------------------------------------------------

void object_parser(t_sdl *sdl, char **param)
{
	if (ft_strequ(param[0], CAMERA))
		init_camera(sdl, param);
	else if (ft_strequ(param[0], SPHERE))
		init_sphere(sdl, param);
	else if (ft_strequ(param[0], PLANE))
		init_plane(sdl, param);
	else if (ft_strequ(param[0], CYLINDER))
		init_cylinder(sdl, param);
	else if (ft_strequ(param[0], CONE))
		init_cone(sdl, param);
	else if (ft_strequ(param[0], LIGHT))
		init_light(sdl, param);
	else if (ft_strequ(param[0], AMBIENT))
		init_ambient(sdl, param);
}

void scene_parser(t_sdl *sdl, char *scene_name)
{
	int fd;
	char *line;
	int ind;
	char **param;

	ind = 0;

	sdl->obj_num = 0;
	sdl->obj_counter = 0;
	sdl->light_num = 0;
	sdl->light_counter = 0;

	sdl->cam_is = 0;

	validate_scene(scene_name, sdl);
	if (!(fd = open(scene_name, O_RDWR)))
		kill_all("Can't open file <scene_parser>");
	//printf("obj_num = %d light_num = %d cam_is = %d", sdl->obj_num, sdl->light_num, sdl->cam_is);

	if (!(sdl->obj = (t_object*)malloc(sizeof(t_object) * sdl->obj_num)))
		kill_all("Can't malloc memory for objects file <scene_parser>");
	if (!(sdl->light = (t_light*)malloc(sizeof(t_light) * sdl->light_num)))
		kill_all("Can't malloc memory for light file <scene_parser>");

	while (get_next_line(fd, &line) > 0)
	{
		param = ft_strsplit(line, ' ');
		ft_strdel(&line);
		object_parser(sdl, param);
		ft_strdel(&line);
		free_mas(param);
	}
	close(fd);
}