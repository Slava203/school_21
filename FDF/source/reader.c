/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:53:08 by daron             #+#    #+#             */
/*   Updated: 2019/10/02 17:56:06 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		push(t_coord **head, t_coord *new)
{
	if (head)
	{
		if (new)
			new->next = *head;
		*head = new;
	}
}

t_coord		*pop(t_coord **head)
{
	t_coord	*top;

	top = NULL;
	if (head && *head)
	{
		top = *head;
		*head = (*head)->next;
	}
	return (top);
}

void		pars_stack(t_coord **head, t_map *map)
{
	t_coord	*top;
	int		i;
	size_t	size;

	size = map->height * map->width * sizeof(int);
	if (!(map->z_coordinate = (int*)malloc(size)))
		kill_pr("Can't allocate memory for z coordinate mas <pars_stack>");
	if (!(map->collor_mas = (int*)malloc(size)))
		kill_pr("Can't allocate memory for color mas <pars_stack>");
	i = map->height * map->width - 1;
	while ((top = pop(head)) && i >= 0)
	{
		map->z_coordinate[i] = top->z;
		map->collor_mas[i] = top->color;
		if (map->max < top->z)
			map->max = top->z;
		if (map->min > top->z)
			map->min = top->z;
		i--;
		free(top);
	}
}

void		pars_string(t_map *map, t_coord **head, char **mas)
{
	int		i;

	i = 0;
	while (mas[i])
	{
		push(head, new_coord(mas[i]));
		i++;
	}
	if (map->width == 0)
		map->width = i;
	else if (map->width != i)
		kill_pr("The Map have error <pars_string>");
}

void		reader(int fd, t_map *map, t_coord **head)
{
	char	*line;
	char	**mas;

	*head = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		if (!(mas = ft_strsplit(line, ' ')))
			kill_pr("Can't work with memory in <reader>");
		pars_string(map, head, mas);
		free_split_mas(mas);
		ft_strdel(&line);
		map->height++;
	}
	if (!(*head))
		kill_pr("Cant't read the map");
}
