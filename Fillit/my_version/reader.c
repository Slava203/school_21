/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 11:18:53 by daron             #+#    #+#             */
/*   Updated: 2019/09/20 12:22:49 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			calculate_min_max(char *str, t_point *min, t_point *max)
{
	int			i;

	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if (i / 5 < min->y)
				min->y = i / 5;
			if (i % 5 < min->x)
				min->x = i % 5;
			if (i / 5 > max->y)
				max->y = i / 5;
			if (i % 5 > max->x)
				max->x = i % 5;
		}
		i++;
	}
}

/*
** n = min x = max
*/

t_tetroming		*refact_tetromino(char *str, char l)
{
	t_point		*n;
	t_point		*x;
	t_tetroming	*ptr;
	char		**mas;
	int			i;

	n = new_point(3, 3);
	x = new_point(0, 0);
	if (!(x && n))
		return (NULL);
	calculate_min_max(str, n, x);
	i = 0;
	if (!(mas = (char**)ft_memalloc(sizeof(char*) * (x->y - n->y + 1))))
		return (NULL);
	while (i < x->y - n->y + 1)
	{
		mas[i] = ft_strnew(x->x - n->x + 1);
		ft_strncpy(mas[i], str + n->x + (n->y + i) * 5, x->x - n->x + 1);
		i++;
	}
	if (!(ptr = new_tetroming(x->x - n->x + 1, x->y - n->y + 1, l, mas)))
		return (NULL);
	ft_memdel((void**)&n);
	ft_memdel((void**)&x);
	return (ptr);
}

int				validate_tetronomius(char *str)
{
	int			i;
	int			block_count;

	i = 0;
	block_count = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if ((i + 1) < 20 && str[i + 1] == '#')
				block_count++;
			if ((i + 5) < 20 && str[i + 5] == '#')
				block_count++;
			if ((i - 1) >= 0 && str[i - 1] == '#')
				block_count++;
			if ((i - 5) >= 0 && str[i - 5] == '#')
				block_count++;
		}
		i++;
	}
	return (block_count == 6 || block_count == 8);
}

int				validate_buf(char *str, size_t read_count)
{
	int			i;
	int			block_count;

	i = 0;
	block_count = 0;
	while (i < 20)
	{
		if (i % 5 < 4)
		{
			if (str[i] == '#' && ++block_count > 4)
				return (1);
			if (!(str[i] == '#' || str[i] == '.'))
				return (2);
		}
		else if (str[i] != '\n')
			return (3);
		i++;
	}
	if ((read_count == 21 && str[20] != '\n') ||
	!(read_count == 21 || read_count == 20))
		return (4);
	return (0);
}

t_list			*read_tetriminos(int fd)
{
	char		buf[21];
	char		letter;
	size_t		read_count;
	t_tetroming	*ptr;
	t_list		*list;

	letter = 'A';
	list = NULL;
	while ((read_count = read(fd, buf, 21)) > 0)
	{
		if ((validate_buf(buf, read_count) != 0) ||
		(validate_tetronomius(buf) != 1))
			return (free_list(list));
		if (!(ptr = refact_tetromino(buf, letter++)))
			return (NULL);
		ft_lst_pushback(&list, ft_lstnew(ptr, sizeof(t_tetroming)));
		ft_memdel((void**)&ptr);
	}
	return (list);
}
