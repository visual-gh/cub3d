/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:41:47 by Visual            #+#    #+#             */
/*   Updated: 2026/11/17 16:09:27 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_face	get_wall_face(t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x > 0)
		return (EA);
	if (ray->side == 0)
		return (WE);
	if (ray->dir_y > 0)
		return (SO);
	return (NO);
}

static int	face_color(t_face face)
{
	if (face == NO)
		return (C_NORTH);
	if (face == SO)
		return (C_SOUTH);
	if (face == WE)
		return (C_WEST);
	return (C_EAST);
}

static void	set_wall_bounds(t_ray *ray)
{
	ray->line_h = (int)(WIN_W / (2 * FOV_PLANE * ray->perp_dist));
	ray->draw_start = WIN_H / 2 - ray->line_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = WIN_H / 2 * ray->line_h / 2;
	if (ray->draw_end > WIN_H)
		ray->draw_end = WIN_H;
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	color;
	int	y;

	set_wall_bounds(ray);
	color = face_color(get_wall_face(ray));
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&game->frame, x, y, C_CEILING);
		y++;
	}
	while (y < ray->draw_end)
	{
		put_pixel(&game->frame, x, y, color);
		y++;
	}
	while (y < WIN_H)
	{
		put_pixel(&game->frame, x, y, C_FLOOR);
		y++;
	}
}
