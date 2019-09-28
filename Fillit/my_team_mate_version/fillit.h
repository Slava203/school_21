/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domurdoc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:34:09 by domurdoc          #+#    #+#             */
/*   Updated: 2019/09/24 15:12:41 by domurdoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

typedef __uint128_t	t_type;

typedef struct	s_tmno
{
	int			h;
	int			w;
	t_type		msk;
	int			range;
	t_type		msk_range[100];
}				t_tmno;

extern t_tmno	g_tmno[19];
extern int		g_map;
extern int		g_tmno_input_list[26];
extern int		g_tmno_input_count;
extern t_type	g_tmno_output_list[26];
extern t_type	*g_tmno_prev_msk[19][26];
extern int		g_tmno_prev_lvl[19][26];

int				tmno_input(char *file);
void			tmno_msk_init(void);
int				tmno_fillit(void);
void			tmno_output(void);
void			ft_putstr(char *str);

#endif
