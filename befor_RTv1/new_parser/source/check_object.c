/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:07:43 by daron             #+#    #+#             */
/*   Updated: 2019/10/31 13:30:44 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void check_object(t_sdl *sdl)
{
	t_light *light;
	t_object *obj;

	light = sdl->light;
	while (light != NULL)
	{
		if (!(light->col.r >= 0 && light->col.r <= 255) || !(light->col.g >= 0 && light->col.g <= 255) || !(light->col.b >= 0 && light->col.b <= 255))
			kill_all("Error in light color <check_object>");
		if(light->inten < 0)
			kill_all("Intensity can't be negative<check_object>");
		light = light->next;
	}
	obj = sdl->obj;
	while (obj != NULL)
	{
		if (!(obj->col.r >= 0 && obj->col.r <= 255) || !(obj->col.g >= 0 && obj->col.g <= 255) || !(obj->col.b >= 0 && obj->col.b <= 255))
			kill_all("Error in object color <check_object>");
		if ((obj->name == SPHERE_ID || obj->name == CYLINDER_ID || obj->name == CONE_ID) && obj->r < EPS)
			kill_all("So small object radius <check_object>");
		if (obj->specular < 0)
			kill_all("Specular can't be negative<check_object>");
		obj = obj->next;
	}
}
