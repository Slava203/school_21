CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c fillit.c input.c init.c output.c
OBJ = $(SRC:.c=.o)
HEAD = fillit.h
NAME = fillit

all: $(NAME)

$(NAME): $(OBJ)

%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
