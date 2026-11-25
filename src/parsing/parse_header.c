/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 14:07:44 by flvejux           #+#    #+#             */
/*   Updated: 2026/11/24 14:27:02 by flvejux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stddef.h>

static int	get_id(char *s)
{
	static char	*ids[ID_COUNT] = {"NO", "SO", "WE", "EA", "F", "C"};
	size_t		len;
	int			i;

	i = 0;
	while (i < ID_COUNT)
	{
		len = ft_strlen(ids[i]);
		if (ft_strncmp(s, ids[i], len) == 0
			&& (s[len] == ' ' || s[len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static void	check_texture_file(t_game *game, char *path)
{
	size_t	len;
	int		fd;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 5) != 0)
		error_exit(game, "texture must be a .xpm file");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(game, "cannot open texture file");
	close(fd);
}

static void	parse_texture(t_game *game, char *value, int id)
{
	int	len;

	if (*value == '\0')
		error_exit(game, "missing texture path");
	len = 0;
	while (value[len] && value[len] != ' ')
		len++;
	if (!is_blank(value + len))
		error_exit(game, "unexpected text after texture path");
	game->tex_path[id] = ft_substr(value, 0, len);
	if (!game->tex_path[id])
		error_exit(game, "malloc failed");
	check_texture_file(game, game->tex_path[id]);
}

static void	parse_element(t_game *game, char *line, int *seen)
{
	int		id;
	char	*value;

	line = skip_spaces(line);
	id = get_id(line);
	if (id == -1)
	{
		error_exit(game, "invalid identifier, or map before all 6 elements");
		return ;
	}
	if (seen[id])
		error_exit(game, "duplicate identifier");
	seen[id] = 1;
	if (id < FACE_COUNT)
		value = skip_spaces(line + 2);
	else
		value = skip_spaces(line + 1);
	if (id < FACE_COUNT)
		parse_texture(game, value, id);
	else if (id == ID_F)
		parse_color(game, value, &game->floor_color);
	else
		parse_color(game, value, &game->ceil_color);
}

int	parse_header(t_game *game)
{
	int	seen[ID_COUNT];
	int	found;
	int	i;

	ft_bzero(seen, sizeof(seen));
	found = 0;
	i = 0;
	while (game->file[i] && found < ID_COUNT)
	{
		if (!is_blank(game->file[i]))
		{
			parse_element(game, game->file[i], seen);
			found++;
		}
		i++;
	}
	if (found < ID_COUNT)
		error_exit(game, "missing element(s): need NO, SO, WE, EA, F and C");
	return (i);
}
