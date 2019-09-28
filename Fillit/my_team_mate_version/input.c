/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domurdoc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:53:06 by domurdoc          #+#    #+#             */
/*   Updated: 2019/09/24 15:23:35 by domurdoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	tmno_input_prev_lvl_init(void)
{
	int i;
	int k;
	int lvl;

	k = -1;
	while (++k < 19)
	{
		lvl = 0;
		i = -1;
		while (++i < g_tmno_input_count)
			if (k == g_tmno_input_list[i])
			{
				g_tmno_prev_lvl[k][i] = lvl;
				lvl = i;
			}
	}
}

int		tmno_input_check(t_type t)
{
	int	i;
	int	k;

	k = -1;
	while (++k < 19)
	{
		i = -1;
		while (++i < g_tmno[k].range)
			if (t == g_tmno[k].msk_range[i])
			{
				g_tmno_input_list[g_tmno_input_count++] = k;
				return (1);
			}
	}
	return (0);
}

void	tmno_input_read_(int *error, char tab[21], t_type *t)
{
	int i;

	i = -1;
	*t = 0;
	while (!*error && ++i < 20)
		if ((i + 1) % 5 == 0)
		{
			if (tab[i] != '\n')
				*error = 1;
		}
		else if (tab[i] == '#')
			*t = (*t << 1) + 1;
		else if (tab[i] == '.')
			*t <<= 1;
		else
			*error = 1;
}

void	tmno_input_read(int fd, int *error)
{
	int		r[2];
	char	tab[21];
	t_type	t;

	while (!*error && (r[0] = read(fd, tab, 21)))
	{
		if ((r[0] < 20 || (r[0] > 20 && tab[20] != '\n')))
			*error = 1;
		else
			tmno_input_read_(error, tab, &t);
		if (g_tmno_input_count == 26 || ((r[1] = r[0]) && !tmno_input_check(t)))
			*error = 1;
	}
	if (r[1] == 21 || g_tmno_input_count == 0)
		*error = 1;
}

int		tmno_input(char *file)
{
	int	fd;
	int	error;

	error = 0;
	fd = open(file, O_RDONLY);
	g_map = 4;
	tmno_msk_init();
	tmno_input_read(fd, &error);
	tmno_input_prev_lvl_init();
	close(fd);
	return (error);
}
