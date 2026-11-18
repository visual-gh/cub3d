/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 17:15:15 by Visual            #+#    #+#             */
/*   Updated: 2026/11/18 01:02:23 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement(t_game *game)
{
	double	step_x;
	double	step_y;

	step_x = game->player.dir_x * MOVE_STEP;
	step_y = game->player.dir_y * MOVE_STEP;
	if (game->keys.w)
		move_player(game, step_x, step_y);
	if (game->keys.s)
		move_player(game, -step_x, -step_y);
	if (game->keys.d)
		move_player(game, -step_y, step_x);
	if (game->keys.a)
		move_player(game, step_y, -step_x);
}

int	game_loop(t_game *game)
{
	if (game->keys.left)
		rotate_player(&game->player, -ROT_STEP);
	if (game->keys.right)
		rotate_player(&game->player, ROT_STEP);
	handle_movement(game);
	render_frame(game);
	return (0);
}
