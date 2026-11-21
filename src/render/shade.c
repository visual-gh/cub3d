/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 15:40:31 by Visual            #+#    #+#             */
/*   Updated: 2026/11/21 19:51:45 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	shade(int color, double factor)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * factor);
	g = (int)(((color >> 8) & 0xFF) * factor);
	b = (int)((color & 0xFF) * factor);
	return ((r << 16) | (g << 8) | b);
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

double	fog_amount(double dist)
{
	double	t;

	t = dist / FOG_DIST;
	if (t > 1.0)
		t = 1.0;
	t = t * t * (3.0 - 2.0 * t);
	return (t * FOG_MAX);
}

int	wall_color(t_img *tex, t_ray *ray, int tex_y)
{
	int	color;

	color = get_texel(tex, ray->tex_x, tex_y);
	color = shade(color, ray->light);
	return (fog(color, ray->fog));
}

void	init_row_colors(t_game *game)
{
	double	dist;
	int		y;

	y = 0;
	while (y < WIN_H / 2)
	{
		dist = WIN_W / (4 * FOV_PLANE * (WIN_H / 2 - y));
		game->row_color[y] = fog(C_CEILING, fog_amount(dist));
		game->row_color[WIN_H - 1 - y] = fog(C_FLOOR, fog_amount(dist));
		y++;
	}
}
