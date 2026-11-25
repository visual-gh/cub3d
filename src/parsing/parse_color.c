/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvejux <flvejux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 14:26:53 by flvejux           #+#    #+#             */
/*   Updated: 2026/11/24 14:27:42 by flvejux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_component(char *s, int *i)
{
	int	value;
	int	digits;

	while (s[*i] == ' ')
		(*i)++;
	value = 0;
	digits = 0;
	while (ft_isdigit(s[*i]))
	{
		value = value * 10 + (s[*i] - '0');
		digits++;
		(*i)++;
		if (digits > 3)
			return (-1);
	}
	while (s[*i] == ' ')
		(*i)++;
	if (digits == 0 || value > 255)
		return (-1);
	return (value);
}

void	parse_color(t_game *game, char *s, int *dst)
{
	int	rgb[3];
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (k < 3)
	{
		rgb[k] = parse_component(s, &i);
		if (rgb[k] < 0)
			error_exit(game, "invalid color: expected R,G,B with values 0-255");
		if (k < 2 && s[i] != ',')
			error_exit(game, "invalid color: expected R,G,B with values 0-255");
		if (k < 2)
			i++;
		k++;
	}
	if (s[i] != '\0')
		error_exit(game, "invalid color: unexpected text after the blue value");
	*dst = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}
