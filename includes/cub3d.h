/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 19:43:09 by Visual            #+#    #+#             */
/*   Updated: 2026/11/24 17:58:55 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <sys/time.h>

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

# define ON_KEYDOWN	2
# define ON_KEYUP	3
# define ON_DESTROY	17

# define WIN_W		1280
# define WIN_H		720
# define C_CEILING	0xA1964C
# define C_FLOOR	0xB9B46D
# define C_LIGHT	0xFFF8E7
# define LIGHT_THRU	0.05
# define FACE_COUNT	4
# define TEX_COUNT	5
# define CEIL_XPM	"textures/ceiling.xpm"
# define PANELS_PER_CELL	2
# define LIGHT_EVERY		2
# define FOV_PLANE	0.66
# define MIN_DIST	0.0001
# define ROT_SPEED	2
# define MOVE_SPEED	3
# define MAX_DT		0.1
# define WALL_GAP	0.2
# define SIDE_SHADE	0.08
# define C_FOG		0x745300
# define FOG_DIST	8
# define FOG_MAX	1.0

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		stride;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef enum e_face
{
	NO,
	SO,
	WE,
	EA,
	CEIL
}	t_face;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	perp_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	light;
	double	fog;
}	t_ray;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_img		frame;
	t_img		tex[TEX_COUNT];
	char		*tex_path[FACE_COUNT];
	t_player	player;
	t_keys		keys;
	double		last_time;
	int			floor_color;
	int			ceil_color;
	double		row_dist[WIN_H / 2];
	double		row_fog[WIN_H / 2];
	int			row_floor[WIN_H / 2];
}	t_game;

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		handle_close(t_game *game);
int		game_loop(t_game *game);
void	rotate_player(t_player *player, double angle);
void	move_player(t_game *game, double move_x, double move_y);

void	init_game(t_game *game);
void	load_textures(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_texel(t_img *tex, int x, int y);
int		render_frame(t_game *game);
void	draw_column(t_game *game, t_ray *ray, int x);
void	draw_ceiling(t_game *game, t_ray *ray, int x);
int		shade(int color, double factor);
int		fog(int color, double t);
double	fog_amount(double dist);
int		tint(int color, int filter);
void	init_row_tables(t_game *game);
void	draw_wall(t_game *game, t_ray *ray, int x);

void	init_test_world(t_game *game);

double	get_time(void);
void	error_exit(t_game *game, char *msg);
void	cleanup(t_game *game);

#endif
