/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 10:11:20 by flvejux           #+#    #+#             */
/*   Updated: 2026/11/25 13:05:35 by flvejux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	last_map_line(t_game *game, int start)
{
	int	end;
	int	i;

	end = start;
	i = start;
	while (game->file[i])
	{
		if (!is_blank(game->file[i]))
			end = i;
		i++;
	}
	return (end);
}

static void	measure_map(t_game *game, int start, int end)
{
	int	len;
	int	i;

	game->map_h = end - start + 1;
	game->map_w = 0;
	i = start;
	while (i <= end)
	{
		if (is_blank(game->file[i]))
			error_exit(game, "empty line inside the map");
		len = ft_strlen(game->file[i]);
		if (len > game->map_w)
			game->map_w = len;
		i++;
	}
}

static char	*pad_line(char *src, int width)
{
	char	*dst;

	dst = malloc(width + 1);
	if (!dst)
		return (NULL);
	ft_memset(dst, ' ', width);
	ft_memcpy(dst, src, ft_strlen(src));
	dst[width] = '\0';
	return (dst);
}

void	extract_map(t_game *game, int start)
{
	int	end;
	int	i;

	while (game->file[start] && is_blank(game->file[start]))
		start++;
	if (!game->file[start])
		error_exit(game, "missing maps");
	end = last_map_line(game, start);
	measure_map(game, start, end);
	game->map = ft_calloc(game->map_h + 1, sizeof(char *));
	if (!game->map)
		error_exit(game, "malloc failed");
	i = 0;
	while (i < game->map_h)
	{
		game->map[i] = pad_line(game->file[start + i], game->map_w);
		if (!game->map[i])
			error_exit(game, "malloc failed");
		i++;
	}
}
