/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:23:22 by Visual            #+#    #+#             */
/*   Updated: 2026/11/17 01:26:06 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
				put_pixel(&game->frame, x, y, C_CEILING);
			else
				put_pixel(&game->frame, x, y, C_FLOOR);
			x++;
		}
		y++;
	}
}

static void	draw_texture(t_game *game, int left, int top)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	y = 0;
	while (y < TEX_SIZE)
	{
		tex_y = y * game->tex.height / TEX_SIZE;
		x = 0;
		while (x < TEX_SIZE)
		{
			tex_x = x * game->tex.width / TEX_SIZE;
			color = get_texel(&game->tex, tex_x, tex_y);
			put_pixel(&game->frame, left + x, top + y, color);
			x++;
		}
		y++;
	}
}

int	render_frame(t_game *game)
{
	draw_background(game);
	draw_texture(game, (WIN_W - TEX_SIZE) / 2, (WIN_H - TEX_SIZE) / 2);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	return (0);
}
