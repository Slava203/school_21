/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:45:49 by daron             #+#    #+#             */
/*   Updated: 2019/09/20 11:08:12 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

# include <stdio.h>

typedef	struct		s_point
{
	int				x;
	int				y;
}					t_point;
/*
 ** width - ширина height - высота
*/

typedef	struct		s_tetroming
{
	int				width;
	int				height;
	char			output_letter;
	char			**tetroming;
}					t_tetroming;

typedef	struct		s_map
{
	int				size;
	char			**map;
}					t_map;

t_list				*read_tetriminos(int fd);
int					validate_buf(char *str, size_t read_count);
int					validate_tetronomius(char *str);
t_tetroming			*refact_tetromino(char *str, char output_letter);
void				calculate_min_max(char *str, t_point *min, t_point *max);

t_point				*new_point(int x, int y);
t_tetroming			*new_tetroming(int width, int height,
		char letter, char **tetroming);
void				*free_list(t_list *list);

t_tetroming			*free_teroming(t_tetroming *ptr);
t_map				*free_map(t_map *tmp, int size);
t_map				*new_map(int size);

int					main(int argc, char **argv);
void				print_map(t_map *map);

void				solver(t_list *list);
int					start_square(int n);
int					check_put_tetroming(t_map *map,
		t_tetroming *tetr, int x, int y);
int					fill_map(t_map *map, t_list *list);
int					put_tetroming(t_tetroming *tetr,
		t_point *point, t_map *map, char c);

#endif
