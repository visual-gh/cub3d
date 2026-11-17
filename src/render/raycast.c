/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 13:18:50 by Visual            #+#    #+#             */
/*   Updated: 2026/11/17 16:10:43 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	t_player	*player;
	double		camera_x;

	player = &game->player;
	camera_x = 2 * x / (double)WIN_W - 1;
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_x = 1e30;
	if (ray->dir_x != 0)
		ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = 1e30;
	if (ray->dir_y != 0)
		ray->delta_y = fabs(1 / ray->dir_y);
}

static void	init_step(t_game *game, t_ray *ray)
{
	t_player	*player;

	player = &game->player;
	ray->step_x = 1;
	ray->side_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (player->pos_x - ray->map_x) * ray->delta_x;
	}
	ray->step_y = 1;
	ray->side_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (player->pos_y - ray->map_y) * ray->delta_y;
	}
}

static void	run_dda(t_game *game, t_ray *ray)
{
	while (game->map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
	if (ray->side == 0)
		ray->perp_dist = ray->side_x - ray->delta_x;
	else
		ray->perp_dist = ray->side_y - ray->delta_y;
	if (ray->perp_dist < MIN_DIST)
		ray->perp_dist = MIN_DIST;
}

int	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray(game, &ray, x);
		init_step(game, &ray);
		run_dda(game, &ray);
		draw_column(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	return (0);
}
