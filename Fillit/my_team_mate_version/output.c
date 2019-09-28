/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domurdoc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:53:28 by domurdoc          #+#    #+#             */
/*   Updated: 2019/09/24 14:54:43 by domurdoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*ft_strnew(int n)
{
	char *str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	while (n >= 0)
		str[n--] = '\0';
	return (str);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	tmno_print(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		ft_putchar(str[i]);
		if ((i + 1) % g_map == 0)
			ft_putchar('\n');
	}
}

void	tmno_output(void)
{
	char	*str;
	char	c;
	int		i;
	int		j;

	i = -1;
	c = 'A';
	str = ft_strnew(g_map * g_map);
	while (++i < g_tmno_input_count)
	{
		j = g_map * g_map;
		while (--j >= 0)
		{
			if ((g_tmno_output_list[i] & 1) == 1)
				str[j] = c;
			else if (!str[j])
				str[j] = '.';
			g_tmno_output_list[i] >>= 1;
		}
		c++;
	}
	tmno_print(str);
	free(str);
}
