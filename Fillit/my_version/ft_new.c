/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:15:19 by daron             #+#    #+#             */
/*   Updated: 2019/09/17 18:22:47 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_point			*new_point(int x, int y)
{
	t_point		*ptr;

	if (!(ptr = (t_point*)malloc(sizeof(t_point))))
		return (NULL);
	ptr->x = x;
	ptr->y = y;
	return (ptr);
}

t_tetroming		*new_tetroming(int width, int height,
		char letter, char **tetroming)
{
	t_tetroming	*ptr;

	if (!(ptr = (t_tetroming*)malloc(sizeof(t_tetroming))))
		return (NULL);
	ptr->width = width;
	ptr->height = height;
	ptr->output_letter = letter;
	ptr->tetroming = tetroming;
	return (ptr);
}

t_map			*new_map(int size)
{
	t_map		*tmp;
	int			i;
	int			j;

	if (!(tmp = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	if (!(tmp->map = (char**)malloc(sizeof(char*) * size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (!(tmp->map[i] = (char*)malloc(sizeof(char) * size)))
			return (free_map(tmp, i + 1));
		j = 0;
		while (j < size)
		{
			tmp->map[i][j] = '.';
			j++;
		}
		i++;
	}
	tmp->size = size;
	return (tmp);
}
