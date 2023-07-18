/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:42:48 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/18 10:30:02 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	// printf("y = %d\n", y);
	// printf("x = %d\n", x);
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
	py = 0;
	while (begin.y > py)
	{
		my_mlx_pixel_put(img, (int)px, (int)py, RGB_DARK_GREY);
		py += dy;
	}
	while (pixels)
	{
		my_mlx_pixel_put(img, (int)px, (int)py, color);
		// printf("begin x = %f\n", px);
		// printf("begin y = %f\n", py);
		px += dx;
		py += dy;
		--pixels;
	}
	while (py < SCREEN_H)
	{
		my_mlx_pixel_put(img, (int)px, (int)py, RGB_DARK_GREY);
		py += dy;
	}	
}

int	draw_frames(t_game *game)
{
	// mlx_clear_window(game->mlx, game->mlx_win);
	// ft_print_mat(game->themap);	
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->data.img, 0, 0);
	update_inputs(game);
	return (0);
}