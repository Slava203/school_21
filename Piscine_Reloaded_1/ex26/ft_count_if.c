/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 18:39:42 by daron             #+#    #+#             */
/*   Updated: 2019/09/02 18:39:45 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int (*f)(char*))
{
	int i;
	int kol;

	i = 0;
	kol = 0;
	while (tab[i] != 0)
	{
		if ((*f)(tab[i]) == 1)
			kol++;
		i++;
	}
	return (kol);
}
