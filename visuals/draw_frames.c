/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:42:48 by dcastagn          #+#    #+#             */
/*   Updated: 2023/08/07 15:35:28 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_colors(t_game *game)
{
	game->data.rgb_fvalue = create_trgb(0, game->parser.f[0], game->parser.f[1],
			game->parser.f[2]);
	game->data.rgb_cvalue = create_trgb(0, game->parser.c[0],
			game->parser.c[1], game->parser.c[2]);
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_background(t_data *img, t_vectors begin, t_vectors end)
{
	img->dx = end.x - begin.x;
	img->dy = end.y - begin.y;
	img->pixels = sqrt((img->dx * img->dx) + (img->dy * img->dy)) + 1;
	img->dx /= img->pixels;
	img->dy /= img->pixels;
	img->px = begin.x;
	img->py = 0;
	while (begin.y > img->py)
	{
		my_mlx_pixel_put(img, (int)img->px, (int)img->py, img->rgb_cvalue);
		img->py += img->dy;
	}
	while (img->pixels)
	{
		img->px += img->dx;
		img->py += img->dy;
		--img->pixels;
	}
	while (img->py < SCREEN_H)
	{
		my_mlx_pixel_put(img, (int)img->px, (int)img->py, img->rgb_fvalue);
		img->py += img->dy;
	}
}

void	draw_line_on(t_data *img, t_vectors begin, t_vectors end, int color)
{
	img->dx = end.x - begin.x;
	img->dy = end.y - begin.y;
	img->pixels = sqrt((img->dx * img->dx) + (img->dy * img->dy)) + 1;
	img->dx /= img->pixels;
	img->dy /= img->pixels;
	img->px = begin.x;
	img->py = 0;
	while (begin.y > img->py)
	{
		my_mlx_pixel_put(img, (int)img->px, (int)img->py, RGB_SKY);
		img->py += img->dy;
	}
	while (img->pixels)
	{
		my_mlx_pixel_put(img, (int)img->px, (int)img->py, color);
		img->px += img->dx;
		img->py += img->dy;
		--img->pixels;
	}
	while (img->py < SCREEN_H)
	{
		my_mlx_pixel_put(img, (int)img->px, (int)img->py, RGB_FLOOR);
		img->py += img->dy;
	}
}

int	draw_frames(t_game *game)
{
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->data.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->mini.data.img,
		game->mini.x, game->mini.y);
	draw_minimap(game);
	update_inputs(game);
	return (0);
}
