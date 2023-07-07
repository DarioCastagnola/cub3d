/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:42:48 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/07 16:15:58 by dcastagn         ###   ########.fr       */
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

void	draw_line_on(t_data *img, t_vectors begin, t_vectors end, int color)
{
	double	dx;
	double	dy;
	double	px;
	double	py;
	int		pixels;

	dx = end.x - begin.x;
	dy = end.y - begin.y;
	pixels = sqrt((dx * dx) + (dy * dy)) + 1;
	dx /= pixels;
	dy /= pixels;
	px = begin.x;
	py = begin.y;
	while (pixels)
	{
		my_mlx_pixel_put(img, (int)px, (int)py, color);
		px += dx;
		py += dy;
		--pixels;
	}
}


int	draw_frames(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	// game->data.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	// game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->data.img, 0, 0);
    usleep(8000);
	return (0);
}