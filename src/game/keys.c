/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:20:40 by Visual            #+#    #+#             */
/*   Updated: 2026/11/18 00:56:02 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_key(t_game *game, int keycode, int state)
{
	if (keycode == KEY_W)
		game->keys.w = state;
	else if (keycode == KEY_A)
		game->keys.a = state;
	else if (keycode == KEY_S)
		game->keys.s = state;
	else if (keycode == KEY_D)
		game->keys.d = state;
	else if (keycode == KEY_LEFT)
		game->keys.left = state;
	else if (keycode == KEY_RIGHT)
		game->keys.right = state;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);
	set_key(game, keycode, 1);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	set_key(game, keycode, 0);
	return (0);
}

int	handle_close(t_game *game)
{
	cleanup(game);
	exit(0);
}
