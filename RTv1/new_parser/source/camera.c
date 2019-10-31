/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:04:45 by daron             #+#    #+#             */
/*   Updated: 2019/10/20 14:21:59 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void init_camera(t_sdl *sdl, char **param)
{
	sdl->cam.pos.x = (double)(ft_atoi(param[1]));
	sdl->cam.pos.y = (double)(ft_atoi(param[2]));
	sdl->cam.pos.z = (double)(ft_atoi(param[3]));

	sdl->cam.rot.x = (double)(ft_atoi(param[4]));
	sdl->cam.rot.y = (double)(ft_atoi(param[5]));
	sdl->cam.rot.z = (double)(ft_atoi(param[6]));
}