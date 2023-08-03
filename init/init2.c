/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:49:57 by dcastagn          #+#    #+#             */
/*   Updated: 2023/08/03 16:33:53 by dcastagn         ###   ########.fr       */
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

void	draw_minimap(t_game *game)
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
			start.x = x * MINIMAP_SCALE;
			start.y = y * MINIMAP_SCALE;
			if (game->parser.map[y][x] == '1')
				draw_square(&game->mini.data, start,
					MINIMAP_SCALE, 0x00FFFFFF);
			else if (game->parser.map[y][x] == 'D')
				draw_square(&game->mini.data, start,
					MINIMAP_SCALE, RGB_GREEN);
			else if (game->parser.map[y][x] == 'd')
				draw_square(&game->mini.data, start,
					MINIMAP_SCALE, RGB_BLUE); 
			else
				draw_square(&game->mini.data, start, MINIMAP_SCALE, 0x00000000);
		}
	}
	start.x = (game->player.pos.x * MINIMAP_SCALE);
	start.y = (game->player.pos.y * MINIMAP_SCALE) - 2;
	draw_square(&game->mini.data, start, MINIMAP_SCALE / 2, 0x00FF0000);
}

void	init_minimap(t_game *game)
{
	game->mini.width = game->parser.mwidth * MINIMAP_SCALE;
	game->mini.height = game->parser.mheight * MINIMAP_SCALE;
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
	int	i;

	game->frames = 0;
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3d");
	game->data.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	game->data.addr = mlx_get_data_addr(game->data.img,
			&game->data.bits_per_pixel, &game->data.line_length,
			&game->data.endian);
	i = -1;
	while (++i < 10)
		game->walls[i].img = NULL;
	init_minimap(game);
}
