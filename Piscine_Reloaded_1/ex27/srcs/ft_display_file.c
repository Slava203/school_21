/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:37:47 by daron             #+#    #+#             */
/*   Updated: 2019/08/14 10:56:38 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

void		print_content(char *filename)
{
	char	buf;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	while (read(fd, &buf, 1) > 0)
		write(1, &buf, 1);
	close(fd);
}

int			main(int argc, char **argv)
{
	if (argc == 1)
		write(1, "File name missing.\n", 19);
	else if (argc > 2)
		write(1, "Too many arguments.\n", 20);
	else
		print_content(argv[1]);
	return (0);
}
