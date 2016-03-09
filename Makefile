# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrosamon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/02 12:17:28 by jrosamon          #+#    #+#              #
#    Updated: 2016/03/09 17:06:47 by jrosamon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = wolf3d

SOURCES = src/main.c \
		  src/event.c\
		  src/draw.c\
		  src/color.c\
		  src/map.c\
		  src/img.c\
		  src/raycasting.c\
		  src/texture.c\
		  src/floor.c

INCLUDES = inc/

OBJECTS = $(subst src,obj,$(subst .c,.o,$(SOURCES)))

LIBSDIR = -L ./lib
LIBS = -lft -lmlx

FRAMEWORK = -framework OpenGL -framework AppKit

LIBFT = libft/libft.a
MLX = mlx/libmlx.a

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJECTS)
	gcc $(FLAGS) $(OBJECTS) $(FRAMEWORK) $(LIBSDIR) $(LIBS) -o $(NAME)

$(LIBFT): ./libft
	@(cd ./libft && $(MAKE))
	cp ./libft/bin/libft.a ./lib
	cp ./libft/inc/libft.h ./inc

$(MLX): ./mlx
	@(cd ./mlx && $(MAKE))
	cp ./mlx/libmlx.a ./lib
	cp ./mlx/mlx.h ./inc

obj/%.o: src/%.c $(INCLUDES)wolf.h
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJECTS)
	@(cd ./libft && $(MAKE) clean)
	@(cd ./mlx && $(MAKE) clean)

fclean:
	@(cd ./libft && $(MAKE) fclean)
	@(cd ./mlx && $(MAKE) clean)
	rm -rf $(OBJECTS)
	rm -rf $(NAME)
	rm -rf ./inc/libft.h
	rm -rf ./inc/mlx.h
	rm -rf ./lib/libft.a
	rm -rf ./lib/libmlx.a

re: fclean all

.PHONY: all clean fclean re
