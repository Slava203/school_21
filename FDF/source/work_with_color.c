/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:11:34 by daron             #+#    #+#             */
/*   Updated: 2019/10/02 17:59:01 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			default_color(int x, t_map *map)
{
	double	percent;
	int		red;
	int		green;
	int		blue;

	percent = ft_percent(map->min, map->max, x);
	red = get_light((FIGURE_START >> 16) & 0xFF,
			(FIGURE_END >> 16) & 0xFF, percent);
	green = get_light((FIGURE_START >> 8) & 0xFF,
			(FIGURE_END >> 8) & 0xFF, percent);
	blue = get_light(FIGURE_START & 0xFF,
			FIGURE_END & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}

int			get_color(t_point cur, t_point start, t_point end, t_point delta)
{
	int		red;
	int		green;
	int		blue;
	double	percent;

	if (cur.collor == end.collor)
		return (cur.collor);
	if (delta.x > delta.y)
		percent = ft_percent(start.x, end.x, cur.x);
	else
		percent = ft_percent(start.y, end.y, cur.y);
	red = get_light((start.collor >> 16) & 0xFF,
			(end.collor >> 16) & 0xFF, percent);
	green = get_light((start.collor >> 8) & 0xFF,
			(end.collor >> 8) & 0xFF, percent);
	blue = get_light(start.collor & 0xFF, end.collor & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}

/*
 ** Return the number on [p1, p2]
*/

int			get_light(int p1, int p2, double percent)
{
	return ((int)((1 - percent) * p1 + percent * p2));
}
