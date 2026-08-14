# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Visual <github.com/visual-gh>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/14 12:11:53 by Visual            #+#    #+#              #
#    Updated: 2026/08/14 13:42:06 by Visual           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
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

SRCS	= src/main.c

OBJS	= $(SRCS:src/%.c=obj/%.o)

all: libft $(MLX) status $(NAME)

# -q reports whether cub3D is stale without building anything
status:
	@$(MAKE) -q --no-print-directory $(NAME) 2>/dev/null \
		&& echo "✅ Nothing to do" || true

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "✅ cub3D"

obj/%.o: src/%.c includes/cub3d.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# -s lets libft's own recipe print only when it actually rebuilds
libft:
	@$(MAKE) -s -C $(LIBFT_DIR)

# vendored sources never change, so a plain file target is enough
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

# subject requires a bonus rule; same binary until bonus sources exist
bonus: all

re: fclean all

# libft recurses every build so its sub-make does its own staleness check
.NOTPARALLEL:
.PHONY: all bonus clean fclean re libft status
