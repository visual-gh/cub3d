/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 17:15:15 by Visual            #+#    #+#             */
/*   Updated: 2026/11/18 18:56:10 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement(t_game *game, double dt)
{
	t_player	*player;
	double		forward;
	double		strafe;
	double		move_x;
	double		move_y;

	player = &game->player;
	forward = (game->keys.w - game->keys.s) * MOVE_SPEED * dt;
	strafe = (game->keys.d - game->keys.a) * MOVE_SPEED * dt;
	if (forward != 0 && strafe != 0)
	{
		forward /= sqrt(2);
		strafe /= sqrt(2);
	}
	move_x = player->dir_x * forward - player->dir_y * strafe;
	move_y = player->dir_y * forward + player->dir_x * strafe;
	move_player(game, move_x, move_y);
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
