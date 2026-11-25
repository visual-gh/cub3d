# **************************************************************************** #
#                                                                              #
#                                                          :::      ::::::::   #
#   Makefile                                             :+:      :+:    :+:   #
#                                                      +:+ +:+         +:+     #
#   By: flvejux <flvejux@student.42lausanne.ch>      +#+  +:+       +#+        #
#                                                  +#+#+#+#+#+   +#+           #
#   Created: 2026/08/14 12:11:53 by Visual              #+#    #+#             #
#   Updated: 2026/11/25 13:48:47 by flvejux            ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -O2
RM		= rm -rf

UNAME	:= $(shell uname)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

ifeq ($(UNAME), Darwin)
	MLX_DIR  = minilibx/mac
	MLXFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm
else
	MLX_DIR  = minilibx/linux
	MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

MLX		= $(MLX_DIR)/libmlx.a
INC		= -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)

SRCS	= src/main.c \
		  src/game/keys.c \
		  src/game/loop.c \
		  src/game/move.c \
		  src/game/rotate.c \
		  src/render/ceiling.c \
		  src/render/color.c \
		  src/render/draw_column.c \
		  src/render/fog.c \
		  src/render/init_mlx.c \
		  src/render/raycast.c \
		  src/render/textures.c \
		  src/render/wall.c \
		  src/utils/cleanup.c \
		  src/utils/error.c \
		  src/utils/timer.c \
		  src/parsing/parse_file.c \
		  src/parsing/read_file.c \
		  src/parsing/parse_header.c \
		  src/parsing/parse_color.c \
		  src/parsing/extract_map.c \
		  src/parsing/check_map.c \
		  src/parsing/set_player.c \
		  src/parsing/parse_utils.c \


OBJS	= $(SRCS:src/%.c=obj/%.o)

all: libft $(MLX) status $(NAME)

# -q reports whether cub3D is stale without building anything
status:
	@$(MAKE) -q --no-print-directory $(NAME) 2>/dev/null \
		&& echo "Nothing to do" || true

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "cub3D Built"

obj/%.o: src/%.c includes/cub3d.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# -s lets libft's own recipe print only when it actually rebuilds
libft:
	@$(MAKE) -s -C $(LIBFT_DIR)

# vendored sources never change, so a plain file target is enough
$(MLX):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1 || $(MAKE) -C $(MLX_DIR)
	@echo "minilibx built"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1
	@$(RM) obj
	@echo "cleaned"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@$(RM) $(NAME)
	@echo "full cleaned"

# subject requires a bonus rule; same binary until bonus sources exist
bonus: all

re: fclean all

# libft recurses every build so its sub-make does its own staleness check
.NOTPARALLEL:
.PHONY: all bonus clean fclean re libft status
