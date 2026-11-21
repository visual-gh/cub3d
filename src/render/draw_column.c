/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:41:47 by Visual            #+#    #+#             */
/*   Updated: 2026/11/21 12:07:08 by Visual           ###   ########.fr       */
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
	double	step;
	double	tex_pos;
	int		tex_y;
	int		y;

	tex = &game->tex[face];
	set_tex_x(game, ray, tex, face);
	step = (double)tex->height / ray->line_h;
	tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_h / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		put_pixel(&game->frame, x, y, get_texel(tex, ray->tex_x, tex_y));
		tex_pos += step;
		y++;
	}
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	y;

	set_wall_bounds(ray);
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&game->frame, x, y, C_CEILING);
		y++;
	}
	draw_wall(game, ray, x, get_wall_face(ray));
	y = ray->draw_end;
	while (y < WIN_H)
	{
		put_pixel(&game->frame, x, y, C_FLOOR);
		y++;
	}
}
