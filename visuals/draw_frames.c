/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:42:48 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/31 16:30:47 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		my_mlx_pixel_put(img, (int)img->px, (int)img->py, RGB_SKY);
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
		my_mlx_pixel_put(img, (int)img->px, (int)img->py, RGB_FLOOR);
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
	// static int	oldmouse;
	// int mouse_diff;
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->data.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->mini.data.img,
		game->mini.x, game->mini.y);
	// mlx_mouse_hide(game->mlx, game->mlx_win);
	// mlx_mouse_get_pos(game->mlx, game->mlx_win, &game->mouse_x, &game->mouse_y);
	// printf("mouse x = %d\n", game->mouse_x);
	// oldmouse = 0;
	// mouse_diff = game->mouse_x - oldmouse;
	// mlx_get_screen_size(game->mlx, &game->screen_x, &game->screen_y);
	// printf("screen x = %d\n screen y = %d\n", game->screen_x, game->screen_y);
	// printf("old mouse = %d\n", oldmouse);
	// printf("diff = %d\n", mouse_diff);
	// if (game->mouse_x < 1270)
	// 	game->player.rot_dir = -1;
	// if (game->mouse_x > 1270)
	// 	game->player.rot_dir = 1;
	// oldmouse = game->mouse_x;
	// printf("rotdir = %f\n", game->player.rot_dir);
	draw_minimap(game);
	update_inputs(game);
	return (0);
}
