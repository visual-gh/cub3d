/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 15:40:48 by Visual            #+#    #+#             */
/*   Updated: 2026/11/24 17:00:07 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	fog_amount(double dist)
{
	double	t;

	t = dist / FOG_DIST;
	if (t > 1.0)
		t = 1.0;
	t = t * t * (3.0 - 2.0 * t);
	return (t * FOG_MAX);
}

int	fog(int color, double t)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r += (int)((((C_FOG >> 16) & 0xFF) - r) * t);
	g += (int)((((C_FOG >> 8) & 0xFF) - g) * t);
	b += (int)(((C_FOG & 0xFF) - b) * t);
	return ((r << 16) | (g << 8) | b);
}

void	init_row_tables(t_game *game)
{
	double	dist;
	int		y;

	y = 0;
	while (y < WIN_H / 2)
	{
		dist = WIN_W / (4 * FOV_PLANE * (WIN_H / 2 - y));
		game->row_dist[y] = dist;
		game->row_fog[y] = fog_amount(dist);
		game->row_floor[y] = fog(game->floor_color, game->row_fog[y]);
		y++;
	}
}
