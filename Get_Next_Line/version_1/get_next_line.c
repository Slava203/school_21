/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:28:57 by daron             #+#    #+#             */
/*   Updated: 2019/09/16 15:33:20 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static size_t		ft_highlight_line(char **line, char *str)
{
	size_t			i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!(*line = ft_strndup(str, i)))
		return (0);
	return (i);
}

static t_list		*ft_next_file_descriptor(int fd,
		t_list **head)
{
	t_list			*tmp;

	if (!head)
	{
		tmp = ft_lstnew("", fd);
		return (tmp);
	}
	tmp = *head;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	ft_lstadd(head, tmp);
	return (tmp);
}

int					ft_read_line(int fd, char **str)
{
	int				read_count;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;

	while ((read_count = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[read_count] = '\0';
		tmp = *str;
		if (!(*str = ft_strjoin(*str, buf)))
			return (-1);
		free(tmp);
		if (ft_strchr(*str, '\n'))
			break ;
	}
	return (read_count);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*elem;
	char			buf[BUFF_SIZE + 1];
	size_t			read_count;
	char			*str;

	if (!line || fd < 0 || !(elem = ft_next_file_descriptor(fd, &head))
	|| (read(fd, buf, 0)) < 0)
		return (-1);
	str = elem->content;
	read_count = ft_read_line(fd, &str);
	elem->content = str;
	if (!read_count && !*str)
		return (0);
	read_count = ft_highlight_line(line, str);
	if (str[read_count] != '\0')
	{
		elem->content = ft_strdup((char*)(str + read_count + 1));
		free(str);
	}
	else
		str[0] = '\0';
	return (1);
}
