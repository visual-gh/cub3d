/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 15:07:22 by Visual            #+#    #+#             */
/*   Updated: 2026/11/13 15:07:55 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(char *msg, t_game *game)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	if (game)
		cleanup(game);
	exit(1);
}
