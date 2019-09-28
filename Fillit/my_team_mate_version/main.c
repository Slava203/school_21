/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domurdoc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:57:00 by domurdoc          #+#    #+#             */
/*   Updated: 2019/09/26 20:13:58 by domurdoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		g_map;
int		g_tmno_input_list[26];
int		g_tmno_input_count;
t_type	g_tmno_output_list[26];
t_type	*g_tmno_prev_msk[19][26];
int		g_tmno_prev_lvl[19][26];

int		main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!tmno_input(av[1]))
		{
			tmno_fillit();
			tmno_output();
		}
		else
			ft_putstr("error\n");
	}
	else
		ft_putstr("usage: ./fillit source_file\n");
	return (0);
}
