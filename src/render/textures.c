/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Visual <github.com/visual-gh>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:14:17 by Visual            #+#    #+#             */
/*   Updated: 2026/11/24 19:05:25 by Visual           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_game *game, t_img *tex, char *path)
{
	tex->ptr = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->ptr)
		error_exit(game, "cannot load texture");
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp,
			&tex->stride, &tex->endian);
}

void	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < FACE_COUNT)
	{
		load_texture(game, &game->tex[i], game->tex_path[i]);
		i++;
	}
	load_texture(game, &game->tex[CEIL], CEIL_XPM);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + y * img->stride + x * (img->bpp / 8);
	*(unsigned int *)dst = color;
}

int	get_texel(t_img *tex, int x, int y)
{
	char	*src;

	src = tex->addr + y * tex->stride + x * (tex->bpp / 8);
	return (*(unsigned int *)src);
}
