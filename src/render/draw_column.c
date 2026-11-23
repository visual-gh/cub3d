/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:41:47 by Visual            #+#    #+#             */
/*   Updated: 2026/11/23 17:54:00 by Visual           ###   ########.fr       */
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

static void	set_tex_x(t_game *game, t_ray *ray, t_img *tex, t_face face)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * tex->width);
	if (face == SO || face == WE)
		ray->tex_x = tex->width - ray->tex_x - 1;
}

static void	draw_wall(t_game *game, t_ray *ray, int x, t_face face)
{
	t_img	*tex;
	int		tex_y;
	int		last_y;
	int		color;
	int		y;

	tex = &game->tex[face];
	set_tex_x(game, ray, tex, face);
	ray->light = 1.0;
	if (ray->side == 0)
		ray->light = 1.0 - SIDE_SHADE;
	ray->fog = fog_amount(ray->perp_dist);
	last_y = -1;
	color = 0;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (y - WIN_H / 2 + ray->line_h / 2) * tex->height / ray->line_h;
		if (tex_y != last_y)
			color = wall_color(tex, ray, tex_y);
		last_y = tex_y;
		put_pixel(&game->frame, x, y, color);
		y++;
	}
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	y;

	set_wall_bounds(ray);
	draw_ceiling(game, ray, x);
	draw_wall(game, ray, x, get_wall_face(ray));
	y = ray->draw_end;
	while (y < WIN_H)
	{
		put_pixel(&game->frame, x, y, game->row_color[y]);
		y++;
	}
}
