/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:47:30 by daron             #+#    #+#             */
/*   Updated: 2019/09/17 18:08:02 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				check_put_tetroming(t_map *map,
		t_tetroming *tetr, int s_n, int c_n)
{
	int			i;
	int			j;

	i = 0;
	while (i < tetr->width)
	{
		j = 0;
		while (j < tetr->height)
		{
			if (tetr->tetroming[j][i] == '#' &&
			map->map[j + c_n][i + s_n] != '.')
				return (0);
			j++;
		}
		i++;
	}
	put_tetroming(tetr, new_point(s_n, c_n), map, tetr->output_letter);
	return (1);
}

int				put_tetroming(t_tetroming *tetr, t_point *point,
		t_map *map, char c)
{
	int			i;
	int			j;

	i = 0;
	while (i < tetr->width)
	{
		j = 0;
		while (j < tetr->height)
		{
			if (tetr->tetroming[j][i] == '#')
				map->map[j + point->y][i + point->x] = c;
			j++;
		}
		i++;
	}
	return (1);
}

int				fill_map(t_map *map, t_list *list)
{
	t_tetroming	*tetr;
	int			i;
	int			j;

	if (list == NULL)
		return (1);
	i = 0;
	tetr = list->content;
	while (i < map->size - tetr->height + 1)
	{
		j = 0;
		while (j < map->size - tetr->width + 1)
		{
			if (check_put_tetroming(map, tetr, j, i))
			{
				if (fill_map(map, list->next))
					return (1);
				else
					put_tetroming(tetr, new_point(j, i), map, '.');
			}
			j++;
		}
		i++;
	}
	return (0);
}

int				start_square(int n)
{
	int			sq_size;

	sq_size = 2;
	while (sq_size * sq_size < 4 * n)
		sq_size++;
	return (sq_size);
}

void			solver(t_list *list)
{
	int			size;
	t_map		*map;

	size = start_square((int)ft_lstcount(list));
	map = new_map(size);
	while (!fill_map(map, list))
	{
		free_map(map, size);
		size++;
		map = new_map(size);
	}
	print_map(map);
	free_map(map, size);
	free_list(list);
}
