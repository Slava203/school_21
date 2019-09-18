# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daron <daron@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 14:19:42 by daron             #+#    #+#              #
#    Updated: 2019/09/14 19:46:35 by daron            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C libft/ fclean && make -C libft/
	@clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
	@clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	@clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft

clean:
	rm -rf *.o
	rm -rf test_gnl

fclean: clean
	@make -C libft/ fclean

re: fclean all
