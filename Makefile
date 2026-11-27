# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Visual <github.com/visual-gh>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/14 12:11:53 by Visual            #+#    #+#              #
#    Updated: 2026/11/27 17:36:43 by Visual           ###   ########.fr        #
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
		  src/parsing/check_map.c \
		  src/parsing/extract_map.c \
		  src/parsing/parse_color.c \
		  src/parsing/parse_file.c \
		  src/parsing/parse_header.c \
		  src/parsing/parse_utils.c \
		  src/parsing/read_file.c \
		  src/parsing/set_player.c \
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
		  src/utils/timer.c

OBJS	= $(SRCS:src/%.c=obj/%.o)

all: libft $(MLX) status $(NAME)

status:
	@$(MAKE) -q --no-print-directory $(NAME) 2>/dev/null \
		&& echo "✅ Nothing to do" || true

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "✅ cub3D"

obj/%.o: src/%.c includes/cub3d.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

libft:
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1 || $(MAKE) -C $(MLX_DIR)
	@echo "✅ minilibx"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1
	@$(RM) obj
	@echo "✅ clean"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@$(RM) $(NAME)
	@echo "✅ fclean"

bonus: all

re: fclean all

.NOTPARALLEL:
.PHONY: all bonus clean fclean re libft status
