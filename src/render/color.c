/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 15:37:35 by Visual            #+#    #+#             */
/*   Updated: 2026/11/24 17:30:08 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	shade(int color, double factor)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * factor);
	g = (int)(((color >> 8) & 0xFF) * factor);
	b = (int)((color & 0xFF) * factor);
	return ((r << 16) | (g << 8) | b);
}

int	tint(int color, int filter)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * ((filter >> 16) & 0xFF) / 255;
	g = ((color >> 8) & 0xFF) * ((filter >> 8) & 0xFF) / 255;
	b = (color & 0xFF) * (filter & 0xFF) / 255;
	return ((r << 16) | (g << 8) | b);
}
