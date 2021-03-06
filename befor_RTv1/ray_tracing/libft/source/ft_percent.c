/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:27:16 by daron             #+#    #+#             */
/*   Updated: 2019/10/02 17:24:43 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		ft_percent(double start, double end, double cur)
{
	double	len;

	len = end - start;
	return ((len == 0) ? 1.0 : ((cur - start) / len));
}
