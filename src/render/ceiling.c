/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 23:32:24 by Visual            #+#    #+#             */
/*   Updated: 2026/11/24 20:59:50 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_panel_edge(double w)
{
	w -= (int)w;
	return (w < PANEL_EDGE || w >= 1.0 - PANEL_EDGE);
}

static int	ceiling_color(t_game *game, double wx, double wy, int y)
{
	int	step;

	wx *= CELL_PANELS;
	wy *= CELL_PANELS;
	if (is_panel_edge(wx) || is_panel_edge(wy))
		return (fog(tint(C_PANEL_EDGE, game->ceil_color), game->row_fog[y]));
	step = CELL_PANELS * LIGHT_EVERY;
	if ((int)wx % step == 0 && (int)wy % step == 0)
		return (fog(C_LIGHT, game->row_fog[y] * (1.0 - LIGHT_THRU)));
	return (fog(game->ceil_color, game->row_fog[y]));
}

void	draw_ceiling(t_game *game, t_ray *ray, int x)
{
	double	wx;
	double	wy;
	int		y;

	y = 0;
	while (y < ray->draw_start)
	{
		wx = game->player.pos_x + game->row_dist[y] * ray->dir_x;
		wy = game->player.pos_y + game->row_dist[y] * ray->dir_y;
		put_pixel(&game->frame, x, y, ceiling_color(game, wx, wy, y));
		y++;
	}
}
