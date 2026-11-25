/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:25:03 by Visual            #+#    #+#             */
/*   Updated: 2026/11/25 13:42:36 by flvejux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < FACE_COUNT)
	{
		if (game->tex[i].ptr)
			mlx_destroy_image(game->mlx, game->tex[i].ptr);
		game->tex[i].ptr = NULL;
		i++;
	}
}

static void	free_parsing(t_game *game)
{
	int	i;

	free_tab(game->file);
	game->file = NULL;
	free_tab(game->map);
	game->map = NULL;
	i = 0;
	while (i < FACE_COUNT)
	{
		free(game->tex_path[i]);
		game->tex_path[i] = NULL;
		i++;
	}
}

void	cleanup(t_game *game)
{
	free_parsing(game);
	destroy_textures(game);
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
