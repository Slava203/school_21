/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:53:12 by daron             #+#    #+#             */
/*   Updated: 2019/09/26 15:42:41 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int kill_pr(char *message)
{
	perror(message);
	ft_putchar('\n');
	exit(1);
}

int main(int argc, char **argv)
{
	int fd;
	t_map *map;
	t_coord *head;
	t_fdf *fdf;

	if (argc != 2)
		kill_pr("usage: fdf map_name");
	if (!(fd = open(argv[1], O_RDWR)))
		kill_pr("Dont't open the file with map");
	map = new_map();
	reader(fd, map, &head);
	close(fd);
	fdf = new_fdf(map);
	fdf->camera = new_camera(fdf);
	pars_stack(&head, map);
	main_draw(fdf);
	button_pres(fdf);
	mlx_loop(fdf->mlx);

	/*int i;
	i = 0;
	while (i < map->height * map->width - 1)
	{
		printf("%d -> %d\n", map->z_coordinate[i], map->collor_mas[i]);
		i++;
	}
	printf("map->max = %d, map->min = %d size = %d", map->max, map->min, map->height * map->width);
	*/
	return (0);
}