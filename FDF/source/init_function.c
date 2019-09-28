/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:58:16 by daron             #+#    #+#             */
/*   Updated: 2019/09/26 13:47:15 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void free_split_mas(char **mas)
{
	int i;

	i = 0;
	while (mas[i])
	{
		free(mas[i]);
		i++;
	}
	free(mas);
}


void push(t_coord **head, t_coord *new)
{
	if (head)
	{
		if (new)
			new->next = *head;
		*head = new;
	}
}

t_coord *pop(t_coord **head)
{
	t_coord *top;

	top = NULL;
	if (head && *head)
	{
		top = *head;
		*head = (*head)->next;
	}
	return (top);
}

t_map *new_map()
{
	t_map *ptr;

	if (!(ptr = (t_map *) malloc(sizeof(t_map))))
		return (NULL);
	ptr->height = 0;
	ptr->width = 0;
	ptr->max = 0;
	ptr->min = INT_MAX;
	ptr->collor_mas = NULL;
	ptr->z_coordinate = NULL;
	return (ptr);
}

t_point new_point(int x, int y, t_map *map)
{
	t_point ptr;
	int ind;

	ind = x + y * map->width;
	ptr.x = x;
	ptr.y = y;
	ptr.z = map->z_coordinate[ind];
	if (map->collor_mas[ind] == -1)
		ptr.collor = default_color(ptr.z, map);
	else
		ptr.collor = map->collor_mas[ind];
	return (ptr);
}

t_coord *new_coord(char *str)
{
	t_coord *ptr;
	char **mas;

	if (!(ptr = (t_coord*)malloc(sizeof(t_coord))))
		kill_pr("Can't create t_coordinate <new_coord>");
	if (!(mas = ft_strsplit(str, ',')))
		kill_pr("Can't split the string <new_coord>");
	if (!ft_isnumber(mas[0], 10))
		kill_pr("Coordinate have a bad base <new_coord>");
	if (mas[1] && !ft_isnumber(mas[1], 16))
		kill_pr("Color have a bad base <new_coord>");
	ptr->z = ft_atoi(mas[0]);
	if (mas[1])
		ptr->color = ft_atoi_base(mas[1], 16);
	else
		ptr->color = -1;
	ptr->next = NULL;
	free_split_mas(mas);
	return (ptr);
}

t_fdf *new_fdf(t_map *map)
{
	t_fdf *ptr;

	if (!(ptr = (t_fdf*)malloc(sizeof(t_fdf))))
		kill_pr("Can't create fdf <new_fdf>");
	ptr->map = map;
	if (!(ptr->mlx = mlx_init()))
		kill_pr("Can't initialize  <mlx_init>");
	if (!(ptr->win = mlx_new_window(ptr->mlx, WIDTH, HEIGHT, "FDF")))
		kill_pr("Can't initialize  <mlx_new_window>");
	if (!(ptr->img = mlx_new_image(ptr->mlx, WIDTH, HEIGHT)))
		kill_pr("Can't initialize  <mlx_new_image>");
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	return (ptr);
}

t_camera *new_camera(t_fdf *fdf)
{
	t_camera *ptr;

	if (!(ptr = (t_camera*)malloc(sizeof(t_camera))))
		kill_pr("Can't create camera <new_camera>");
	ptr->alp = 0;
	ptr->bet = 0;
	ptr->gam = 0;
	ptr->x_offset = 0;
	ptr->y_offset = 0;
	ptr->z_divisor = 1;
	ptr->zoom = FT_MIN((WIDTH - MENU_WIDTH) / fdf->map->width / 2, HEIGHT / fdf->map->height / 2);
	return (ptr);
}