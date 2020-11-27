/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 10:00:47 by daron             #+#    #+#             */
/*   Updated: 2019/09/09 12:24:22 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strclr(char *s)
{
	size_t	i;
	char	*ptr;

	if (s == NULL)
		return ;
	i = 0;
	ptr = s;
	if (ptr)
	{
		while (ptr[i] != '\0')
		{
			s[i] = '\0';
			i++;
		}
	}
}
