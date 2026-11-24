/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 08:15:18 by flvejux           #+#    #+#             */
/*   Updated: 2026/11/24 11:26:56 by flvejux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stdlib.h>

static int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

static char	**tab_append(char **tab, char *line)
{
	char	**new;
	int		len;
	int		i;

	len = tab_len(tab);
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = tab[i];
		i++;
	}
	new[len] = line;
	new[len + 1] = NULL;
	free(tab);
	return (new);
}

static void	strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1 == '\n'])
	{
		len--;
		line[len] = '\0';
	}
	if (len > 0 && line[len - 1] == '\r')
		line[len - 1] = '\0';
}

void	read_file(t_game *game, char *path)
{
	int		fd;
	char	*line;
	char	**new;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("cannot open map file", game);
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		new = tab_append(game->file, line);
		if (!new)
		{
			free(line);
			close(fd);
			error_exit("malloc failed", game);
		}
		game->file = new;
		line = get_next_line(fd);
	}
	close(fd);
	if (!game->file)
		error_exit("map file is empty or unreadable", game);
}
