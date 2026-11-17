/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 17:15:15 by Visual            #+#    #+#             */
/*   Updated: 2026/11/17 17:22:27 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	if (game->keys.left)
		rotate_player(&game->player, -ROT_STEP);
	if (game->keys.right)
		rotate_player(&game->player, ROT_STEP);
	render_frame(game);
	return (0);
}
