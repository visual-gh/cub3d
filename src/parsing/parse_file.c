/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 08:05:41 by flvejux           #+#    #+#             */
/*   Updated: 2026/11/24 11:25:19 by flvejux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_cub_ext(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".cub", 5) != 0)
		return (0);
	if (path[len - 5] == '/')
		return (0);
	return (1);
}

void	check_args(int argc, char **argv)
{
	if (argc != 2)
		error_exit(NULL, "usage: ./cub3D <map.cub>");
	if (!has_cub_ext(argv[1]))
		error_exit(NULL, "map file must have a .cub extension");
}

void	parse_file(t_game *game, char *path)
{
	int	map_start;

	read_file(game, path);
	map_start = parse_header(game);
	extract_map(game, map_start);
	check_map(game);
	set_player(game);
	free_tab(game->file);
	game->file = NULL;
}
