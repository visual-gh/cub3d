/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 11:48:32 by Visual            #+#    #+#             */
/*   Updated: 2026/11/23 16:34:32 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_test_map(t_game *game)
{
		static char	*map[] = {
				"1111111111",
				"1000000001",
				"1001100001",
				"1000000101",
				"10000N0001",
				"1111111111",
				NULL
		};

		game->map = map;
}

static void	set_test_textures(t_game *game)
{
	game->tex_path[NO] = "textures/north.xpm";
	game->tex_path[SO] = "textures/south.xpm";
	game->tex_path[WE] = "textures/west.xpm";
	game->tex_path[EA] = "textures/east.xpm";
}

static void	set_test_player(t_player *player)
{
	player->pos_x = 5.5;
	player->pos_y = 4.5;
	player->dir_x = 0.0;
	player->dir_y = -1.0;
	player->plane_x = FOV_PLANE;
	player->plane_y = 0.0;
}

void	init_test_world(t_game *game)
{
	set_test_map(game);
	set_test_player(&game->player);
	set_test_textures(game);
	game->floor_color = C_FLOOR;
	game->ceil_color = C_CEILING;
}
