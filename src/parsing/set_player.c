/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 12:59:17 by flvejux           #+#    #+#             */
/*   Updated: 2026/11/25 12:59:21 by flvejux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir(t_player *p, double dir_x, double dir_y)
{
	p->dir_x = dir_x;
	p->dir_y = dir_y;
	p->plane_x = -dir_y * FOV_PLANE;
	p->plane_y = dir_x * FOV_PLANE;
}

void	set_player(t_game *game)
{
	char	c;
	int		x;
	int		y;

	x = (int)game->player.pos_x;
	y = (int)game->player.pos_y;
	c = game->map[y][x];
	if (c == 'N')
		set_dir(&game->player, 0, -1);
	else if (c == 'S')
		set_dir(&game->player, 0, 1);
	else if (c == 'E')
		set_dir(&game->player, 1, 0);
	else
		set_dir(&game->player, -1, 0);
	game->map[y][x] = '0';
}
