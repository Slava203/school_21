/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:46:06 by daron             #+#    #+#             */
/*   Updated: 2019/09/02 18:13:04 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int *ptr;
	int i;
	int k;

	if (min >= max)
	{
		ptr = NULL;
		return (0);
	}
	i = 0;
	k = min;
	ptr = (int*)malloc(sizeof(*ptr) * (max - min));
	while (k <= max)
	{
		ptr[i] = k;
		i++;
		k++;
	}
	return (ptr);
}
