/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domurdoc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:56:16 by domurdoc          #+#    #+#             */
/*   Updated: 2019/09/24 15:16:38 by domurdoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		sqrt_up(int nb)
{
	int	x;

	x = 1;
	while (x * x < nb)
		x++;
	return (x);
}

t_type	*tmno_msk_match_next(t_type base, int k, int level)
{
	t_type	*prev;
	t_type	*curr;
	t_type	*last;

	prev = g_tmno_prev_msk[k][level];
	last = &g_tmno[k].msk_range[g_tmno[k].range - 1];
	if (prev < last)
	{
		curr = prev ? prev + 1 : &g_tmno[k].msk_range[0];
		while (curr <= last)
		{
			if (!(base & *curr))
				return (curr);
			curr++;
		}
	}
	return (NULL);
}

int		tmno_recursion(t_type base, int level)
{
	t_type	*addr;
	int		out;
	int		k;

	k = g_tmno_input_list[level];
	g_tmno_prev_msk[k][level] = g_tmno_prev_msk[k][g_tmno_prev_lvl[k][level]];
	out = 0;
	if (level == g_tmno_input_count)
		return (1);
	while (!out && (addr = tmno_msk_match_next(base, k, level)))
	{
		g_tmno_prev_msk[k][level] = addr;
		out = tmno_recursion((*addr | base), level + 1);
	}
	g_tmno_output_list[level] = out ? *addr : 0;
	return (out);
}

int		tmno_fillit(void)
{
	int	out;
	int	i;
	int	j;

	g_map = sqrt_up(g_tmno_input_count * 4);
	tmno_msk_init();
	while (g_map < 12 && !(out = tmno_recursion(0, 0)))
	{
		g_map++;
		tmno_msk_init();
		i = -1;
		while (++i < 19)
		{
			j = -1;
			while (++j < 26)
				g_tmno_prev_msk[i][j] = NULL;
		}
	}
	return (out);
}
