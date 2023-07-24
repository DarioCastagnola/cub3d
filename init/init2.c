/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:49:57 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/24 14:40:55 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_minimap(t_game *game)
{
    int cell_width = MINIMAP_SIZE / game->parser.mwidth;
    int cell_height = MINIMAP_SIZE / game->parser.mheight;
    int y = -1;

    while (++y < game->parser.mheight)
    {
        int x = -1;
        while (++x < game->parser.mwidth)
        {
            int cell_type = game->parser.map[y][x];
            int rect_x = x * cell_width;
            int rect_y = y * cell_height;
            int color = 0x000000; //nero
            if (cell_type == '1')
                color = 0xFFFFFF; //bianco
            mlx_string_put(game->mlx, game->mlx_win, rect_x + 10, rect_y + 10, color, "1");
        }
    }
    int player_minimap_x = game->player.pos.x * MINIMAP_SCALE;
    int player_minimap_y = game->player.pos.y * MINIMAP_SCALE;
    mlx_string_put(game->mlx, game->mlx_win, player_minimap_x, player_minimap_y + 100, 0xFF0000, "X");}

void	init_minimap(t_game *game)
{
	game->mini.width = game->parser.mwidth * 15;
	game->mini.height = game->parser.mheight * 25;
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
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3d");
	game->data.img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	game->data.addr = mlx_get_data_addr(game->data.img,
			&game->data.bits_per_pixel, &game->data.line_length,
			&game->data.endian);
	init_minimap(game);
}
