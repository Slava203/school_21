/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:05:36 by daron             #+#    #+#             */
/*   Updated: 2019/11/16 12:48:58 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void init_ambient(t_sdl *sdl, char **param)
{
	sdl->ambient = (double)(atoi(param[1])) / 100;
	if (sdl->ambient < 0)
		kill_all("Are you kidding, it can't be lover then zero <init_ambient>");
}
