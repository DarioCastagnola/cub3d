/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:49:57 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/18 15:14:26 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_minimap_back_and_player(t_game *game)
{
	t_vectors	begin;
	t_vectors	end;

	begin.x = 0;
	begin.y = 0;
	end.x = game->mini.width;
	end.y = game->mini.height;
	draw_rect_on(&game->mini.data, begin, end, RGB_DARK_GREY);
	begin.x = (int)(game->player.pos.x * 5) - 1;
	begin.y = (int)(game->player.pos.y * 5) - 2;
	end.x = (int)(game->player.pos.x * 5) + 2;
	end.y = (int)(game->player.pos.y * 5) + 2;
	draw_rect_on(&game->mini.data, begin, end, RGB_RED);
}

void	init_minimap(t_game *game)
{
	game->mini.width = game->parser.mwidth * 5 + 1;
	game->mini.height = game->parser.mheight * 5 + 1;
	game->mini.x = SCREEN_W - game->mini.width - 5;
	game->mini.y = 5;
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
