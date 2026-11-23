/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 23:32:24 by Visual            #+#    #+#             */
/*   Updated: 2026/11/23 11:57:16 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	tint(int texel, int color)
{
	int	r;
	int	g;
	int	b;

	r = ((texel >> 16) & 0xFF) * ((color >> 16) & 0xFF) / 255;
	g = ((texel >> 8) & 0xFF) * ((color >> 8) & 0xFF) / 255;
	b = (texel & 0xFF) * (color & 0xFF) / 255;
	return ((r << 16) | (g << 8) | b);
}

static int	ceiling_color(t_game *game, double wx, double wy, int y)
{
	t_img	*tex;
	int		px;
	int		py;
	int		color;

	tex = &game->tex[CEIL];
	wx *= PANELS_PER_CELL;
	wy *= PANELS_PER_CELL;
	px = (int)wx;
	py = (int)wy;
	color = get_texel(tex, (int)((wx - px) * tex->width),
					(int)((wy - py) * tex->height));
	return (fog(tint(color, C_CEILING), game->row_fog[y]));
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
