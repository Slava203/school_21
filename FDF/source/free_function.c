/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:00:59 by daron             #+#    #+#             */
/*   Updated: 2019/10/02 18:03:07 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split_mas(char **mas)
{
	int	i;

	i = 0;
	while (mas[i])
	{
		free(mas[i]);
		i++;
	}
	free(mas);
}

void	free_fdf(t_fdf *fdf)
{
	free(fdf->map->z_coordinate);
	free(fdf->map->collor_mas);
	free(fdf->map);
	free(fdf->camera);
	free(fdf->data_addr);
	free(fdf->img);
	free(fdf->win);
	free(fdf->mlx);
	free(fdf);
}
