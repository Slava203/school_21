NAME = RTv1
SRC = source/main.c \
		source/scene_parser.c \
		source/string_parser.c \
		source/cone.c \
		source/plane.c \
		source/sphere.c \
		source/cylinder.c \
		source/check_object.c \
		source/ray_tracing.c \
		source/init_function.c \
		source/light.c \
		source/event.c

OBJ = $(SRC:.c=.o)
LIBS = libft/libft.a ftvector/ftvector.a
HEADERS = -I ./includes -I ./libft/includes -I ./ftvector/includes
HDR = includes/RTv1.h
FLAGS = -Wall -Wextra -Werror
CGFLAGS = -lmlx -framework OpenGL -framework AppKit
INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks/
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer

all: $(NAME)

$(NAME): libft/libft.a ftvector/ftvector.a $(OBJ) $(HDR)
	@gcc $(FLAGS) $(CGFLAGS) $(FRAMEWORKS) $(OBJ) $(LIBS) -o $(NAME)
	@printf "Compailing RTv1 done\n"

.c.o: $(HDR)
	@gcc $(FLAGS) $(INCLUDES) $(HEADERS) -c $< -o $@

clean:
	@make clean -C libft
	@make clean -C ftvector
	@rm -rf $(OBJ)
	@printf "All objects of RTv1 was deleted\n"

fclean:
	@make fclean -C libft
	@make fclean -C ftvector
	@rm -rf $(OBJ)
	@rm -rf $(NAME)
	@printf "All objects and binary of RTv1 was deleted\n"

libft/libft.a:
	@make -C libft

ftvector/ftvector.a:
	@make -C ftvector

re: fclean all
