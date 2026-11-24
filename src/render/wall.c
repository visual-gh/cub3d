/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:12:21 by Visual            #+#    #+#             */
/*   Updated: 2026/11/24 17:20:15 by Visual           ###   ########.fr       */
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

static void	set_tex_x(t_game *game, t_ray *ray, t_img *tex)
{
	double	wall_x;
	t_face	face;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * tex->width);
	face = get_wall_face(ray);
	if (face == SO || face == WE)
		ray->tex_x = tex->width - ray->tex_x - 1;
}

static int	wall_color(t_img *tex, t_ray *ray, int tex_y)
{
	int	color;

	color = get_texel(tex, ray->tex_x, tex_y);
	color = shade(color, ray->light);
	return (fog(color, ray->fog));
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	int		tex_y;
	int		last_y;
	int		color;
	int		y;

	tex = &game->tex[get_wall_face(ray)];
	set_tex_x(game, ray, tex);
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
