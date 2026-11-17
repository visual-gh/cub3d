/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 17:12:31 by Visual            #+#    #+#             */
/*   Updated: 2026/11/17 21:53:58 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *player, double angle)
{
	double	cos_a;
	double	sin_a;
	double	old_x;

	cos_a = cos(angle);
	sin_a = sin(angle);
	old_x = player->dir_x;
	player->dir_x = old_x * cos_a - player->dir_y * sin_a;
	player->dir_y = old_x * sin_a + player->dir_y * cos_a;
	old_x = player->plane_x;
	player->plane_x = old_x * cos_a - player->plane_y * sin_a;
	player->plane_y = old_x * sin_a + player->plane_y * cos_a;
}
