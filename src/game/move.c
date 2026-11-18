/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 21:57:46 by Visual            #+#    #+#             */
/*   Updated: 2026/11/18 02:27:37 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_game *game, double x, double y)
{
	return (game->map[(int)y][(int)x] == '1');
}

static int	hits_wall(t_game *game, double x, double y)
{
	return (is_wall(game, x - WALL_GAP, y - WALL_GAP)
			|| is_wall(game, x + WALL_GAP, y - WALL_GAP)
			|| is_wall(game, x - WALL_GAP, y + WALL_GAP)
			|| is_wall(game, x + WALL_GAP, y + WALL_GAP));
}

void	move_player(t_game *game, double move_x, double move_y)
{
	t_player	*player;

	player = &game->player;
	if (!hits_wall(game, player->pos_x + move_x, player->pos_y))
		player->pos_x += move_x;
	if (!hits_wall(game, player->pos_x, player->pos_y + move_y))
		player->pos_y += move_y;
}
