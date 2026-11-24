/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 23:32:24 by Visual            #+#    #+#             */
/*   Updated: 2026/11/24 17:20:50 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	panel_texel(t_img *tex, double wx, double wy)
{
	return (get_texel(tex, (int)((wx - (int)wx) * tex->width),
		(int)((wy - (int)wy) * tex->height)));
}

static int	ceiling_color(t_game *game, double wx, double wy, int y)
{
	int	step;
	int	color;

	wx *= PANELS_PER_CELL;
	wy *= PANELS_PER_CELL;
	step = PANELS_PER_CELL * LIGHT_EVERY;
	color = panel_texel(&game->tex[CEIL], wx, wy);
	if ((int)wx % step == 0 && (int)wy % step == 0 && color == 0xFFFFFF)
		return (fog(C_LIGHT, game->row_fog[y] * (1.0 - LIGHT_THRU)));
	return (fog(tint(color, game->ceil_color), game->row_fog[y]));
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
