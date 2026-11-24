/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:04:17 by Visual            #+#    #+#             */
/*   Updated: 2026/11/24 17:54:34 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	ft_memset(&game, 0, sizeof(game));
	init_test_world(&game);
	init_row_tables(&game);
	init_game(&game);
	mlx_hook(game.win, ON_KEYDOWN, 1L << 0, key_press, &game);
	mlx_hook(game.win, ON_KEYUP, 1L << 1, key_release, &game);
	mlx_hook(game.win, ON_DESTROY, 0, handle_close, &game);
	game.last_time = get_time();
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
