/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 21:57:46 by Visual            #+#    #+#             */
/*   Updated: 2026/11/18 01:09:12 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + move_x;
	new_y = game->player.pos_y + move_y;
	if (game->map[(int)new_y][(int)new_x] == '1')
		return ;
	game->player.pos_x = new_x;
	game->player.pos_y = new_y;
}
