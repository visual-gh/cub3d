/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 19:43:09 by Visual            #+#    #+#             */
/*   Updated: 2026/11/14 15:35:08 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"

# ifdef __linux__
#  define KEY_ESC	65307
#  define KEY_W		119
#  define KEY_A		97
#  define KEY_S		115
#  define KEY_D		100
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
# else
#  define KEY_ESC	53
#  define KEY_W		13
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_LEFT	123
#  define KEY_RIGHT	124
# endif

# define WIN_W		1280
# define WIN_H		720

typedef struct s_game
{
	void	*mlx;
	void	*win;
}	t_game;

int		key_press(int keycode, t_game *game);
int		handle_close(t_game *game);

void	init_game(t_game *game);

void	error_exit(char *msg, t_game *game);
void	cleanup(t_game *game);

#endif
