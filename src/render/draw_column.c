/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:41:47 by Visual            #+#    #+#             */
/*   Updated: 2026/11/24 17:12:18 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_wall_bounds(t_ray *ray)
{
	ray->line_h = (int)(WIN_W / (2 * FOV_PLANE * ray->perp_dist));
	ray->draw_start = WIN_H / 2 - ray->line_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = WIN_H / 2 + ray->line_h / 2;
	if (ray->draw_end > WIN_H)
		ray->draw_end = WIN_H;
}

static void	draw_floor(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_end;
	while (y < WIN_H)
	{
		put_pixel(&game->frame, x, y, game->row_floor[WIN_H - 1 - y]);
		y++;
	}
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	set_wall_bounds(ray);
	draw_ceiling(game, ray, x);
	draw_wall(game, ray, x);
	draw_floor(game, ray, x);
}
