/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:48:56 by daron             #+#    #+#             */
/*   Updated: 2019/09/02 16:49:08 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(char c);

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_swap(int i, int j, char **mas)
{
	char *buf;

	buf = *(mas + i);
	*(mas + i) = *(mas + j);
	*(mas + j) = buf;
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}

void	sort_mas(int size, char **mas)
{
	int j;
	int i;

	i = 1;
	while (i < size)
	{
		j = 1;
		while (j < size - 1)
		{
			if (ft_strcmp(mas[i], mas[j]) < 0)
			{
				ft_swap(i, j, mas);
			}
			j++;
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	int i;

	i = 1;
	sort_mas(argc, argv);
	i = 1;
	while (i < argc)
	{
		ft_putstr(argv[i]);
		i++;
		ft_putchar('\n');
	}
	return (0);
}
