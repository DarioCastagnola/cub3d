/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:42:48 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/11 11:58:09 by dcastagn         ###   ########.fr       */
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

void	draw_line_on(t_game *game, t_vectors begin, t_vectors end, int color)
{
	double	dx;
	double	dy;
	double	px;
	double	py;
	int		pixels;

	dx = end.x - (int)begin.x;
	dy = end.y - (int)begin.y;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	px = (int)begin.x;
	py = (int)begin.y;
	while (pixels)
	{
		printf("%f %f\n\n", px, py);
		my_mlx_pixel_put(game->data.img, (int)px, (int)py, color);
		px += dx;
		py += dy;
		--pixels;
	}
}

int	draw_frames(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->data.img, 0, 0);
    usleep(8000);
	return (0);
}