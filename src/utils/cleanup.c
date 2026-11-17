/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:25:03 by Visual            #+#    #+#             */
/*   Updated: 2026/11/16 16:29:26 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup(t_game *game)
{
	if (game->tex.ptr)
		mlx_destroy_image(game->mlx, game->tex.ptr);
	game->tex.ptr = NULL;
	if (game->frame.ptr)
		mlx_destroy_image(game->mlx, game->frame.ptr);
	game->frame.ptr = NULL;
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	game->mlx = NULL;
}
