/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 15:40:31 by Visual            #+#    #+#             */
/*   Updated: 2026/11/21 17:51:30 by Visual           ###   ########.fr       */
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
