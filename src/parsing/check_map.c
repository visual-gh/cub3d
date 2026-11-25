/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 10:54:16 by flvejux           #+#    #+#             */
/*   Updated: 2026/11/25 13:45:15 by flvejux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_chars(t_game *game)
{
	int	players;
	int	x;
	int	y;

	players = 0;
	y = -1;
	while (++y < game->map_h)
	{
		x = -1;
		while (++x < game->map_w)
		{
			if (!ft_strchr("01NSEW ", game->map[y][x]))
				error_exit(game, "invalid char in map");
			if (ft_strchr("NSEW", game->map[y][x]))
			{
				players++;
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
			}
		}
	}
	if (players != 1)
		error_exit(game, "map must contain only one player (N, S, E or W)");
}

static int	is_open(t_game *game, int x, int y)
{
	char	**map;

	map = game->map;
	if (y == 0 || x == 0 || y == game->map_h - 1 || x == game->map_w - 1)
		return (1);
	return (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ');
}

static void	check_closed(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map_h)
	{
		x = -1;
		while (++x < game->map_w)
		{
			if (ft_strchr("0NSEW", game->map[y][x]) && is_open(game, x, y))
				error_exit(game, "map is not closed by walls");
		}
	}
}

void	check_map(t_game *game)
{
	check_chars(game);
	check_closed(game);
}
