/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:49:57 by dcastagn          #+#    #+#             */
/*   Updated: 2023/08/07 15:33:22 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_data *img, t_vectors start, int side, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < side)
	{
		x = -1;
		while (++x < side)
			my_mlx_pixel_put(img, x + start.x, y + start.y, color);
	}
}

void	minimap_colorinmap(t_game *game)
{
	int			x;
	int			y;
	t_vectors	start;

	y = -1;
	while (game->parser.map[++y])
	{
		x = -1;
		while (game->parser.map[y][++x])
		{
			start.x = x * game->mscale;
			start.y = y * game->mscale;
			if (game->parser.map[y][x] == '1')
				draw_square(&game->mini.data, start,
					game->mscale, 0x00FFFFFF);
			else if (game->parser.map[y][x] == 'D')
				draw_square(&game->mini.data, start,
					game->mscale, RGB_GREEN);
			else if (game->parser.map[y][x] == 'd')
				draw_square(&game->mini.data, start,
					game->mscale, RGB_BLUE); 
			else
				draw_square(&game->mini.data, start, game->mscale, 0x00000000);
		}
	}
}

void	draw_minimap(t_game *game)
{
	t_vectors	start;

	minimap_colorinmap(game);
	start.x = (game->player.pos.x * game->mscale);
	start.y = (game->player.pos.y * game->mscale) - 2;
	draw_square(&game->mini.data, start, game->mscale / 2, 0x00FF0000);
}

void	init_minimap(t_game *game)
{
	game->mscale = (int)(SCREEN_W / 150);
	game->mini.width = game->parser.mwidth * game->mscale;
	game->mini.height = game->parser.mheight * game->mscale;
	game->mini.x = 0;
	game->mini.y = 0;
	game->mini.data.img = mlx_new_image(game->mlx, game->mini.width,
			game->mini.height);
	game->mini.data.addr = mlx_get_data_addr(game->mini.data.img,
			&game->mini.data.bits_per_pixel, &game->mini.data.line_length,
			&game->mini.data.endian);
}

void	init_game(t_game *game)
{
	game->frames = 0;
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3d");
	game->data.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	game->data.addr = mlx_get_data_addr(game->data.img,
			&game->data.bits_per_pixel, &game->data.line_length,
			&game->data.endian);
	init_minimap(game);
}
