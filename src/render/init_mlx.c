/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:48:59 by Visual            #+#    #+#             */
/*   Updated: 2026/11/24 19:04:22 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_frame(t_game *game)
{
	t_img	*frame;

	frame = &game->frame;
	frame->ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!frame->ptr)
		error_exit(game, "mlx_new_image failed");
	frame->addr = mlx_get_data_addr(frame->ptr, &frame->bpp,
			&frame->stride, &frame->endian);
	frame->width = WIN_W;
	frame->height = WIN_H;
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit(game, "mlx_init failed");
	load_textures(game);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		error_exit(game, "mlx_new_window failed");
	init_frame(game);
}
