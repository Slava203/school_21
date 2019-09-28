# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daron <daron@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/12 14:41:47 by daron             #+#    #+#              #
#    Updated: 2019/09/20 11:02:51 by daron            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=fillit

all: $(NAME)

$(NAME):
	@make -C libft/ fclean && make -C libft/
	@gcc -Wall -Wextra -Werror -I libft/includes -o reader.o -c reader.c
	@gcc -Wall -Wextra -Werror -I libft/includes -o ft_new.o -c ft_new.c
	@gcc -Wall -Wextra -Werror -I libft/includes -o ft_free.o -c ft_free.c
	@gcc -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	@gcc -Wall -Wextra -Werror -I libft/includes -o solver.o -c solver.c
	@gcc -o $(NAME) reader.o ft_free.o ft_new.o main.o solver.o -I libft/includes -L libft/ -lft

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
