/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 17:15:15 by Visual            #+#    #+#             */
/*   Updated: 2026/11/18 01:24:12 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement(t_game *game, double dt)
{
	double	step_x;
	double	step_y;

	step_x = game->player.dir_x * MOVE_SPEED * dt;
	step_y = game->player.dir_y * MOVE_SPEED * dt;
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
	double	now;
	double	dt;

	now = get_time();
	dt = now - game->last_time;
	game->last_time = now;
	if (dt > MAX_DT)
		dt = MAX_DT;
	if (dt < 0)
		dt = 0;
	if (game->keys.left)
		rotate_player(&game->player, -ROT_SPEED * dt);
	if (game->keys.right)
		rotate_player(&game->player, ROT_SPEED * dt);
	handle_movement(game, dt);
	render_frame(game);
	return (0);
}
