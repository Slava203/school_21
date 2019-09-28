/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:20:02 by daron             #+#    #+#             */
/*   Updated: 2019/09/17 18:20:02 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			*free_list(t_list *list)
{
	t_list		*next;
	t_tetroming	*tetr;

	while (list)
	{
		tetr = list->content;
		free_teroming(tetr);
		next = list->next;
		ft_memdel((void**)&list);
		list = next;
	}
	return (NULL);
}

t_tetroming		*free_teroming(t_tetroming *ptr)
{
	int			i;

	i = 0;
	while (i < ptr->height)
	{
		ft_memdel((void**)&ptr->tetroming[i]);
		i++;
	}
	ft_memdel((void**)&(ptr->tetroming));
	ft_memdel((void**)&ptr);
	return (NULL);
}

t_map			*free_map(t_map *tmp, int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		ft_memdel((void**)&(tmp->map[i]));
		i++;
	}
	ft_memdel((void**)&tmp->map);
	ft_memdel((void**)&tmp);
	return (NULL);
}
