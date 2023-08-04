/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:15:09 by dcastagn          #+#    #+#             */
/*   Updated: 2023/08/04 14:26:00 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_texture_x(t_game *game)
{
	double	wall_x;
	int		tex_x;

	if (game->ray.side == 0)
		wall_x = game->player.pos.y + game->ray.perp_wall_dist
			* game->ray.ray_dir.y;
	else
		wall_x = game->player.pos.x + game->ray.perp_wall_dist
			* game->ray.ray_dir.x;
	wall_x -= (int)(wall_x);
	tex_x = (int)(wall_x * (double)(game->walls[game->ray.color].width));
	if (game->ray.side == 0 && game->ray.ray_dir.x > 0)
		tex_x = game->walls[game->ray.color].width - tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir.y < 0)
		tex_x = game->walls[game->ray.color].width - tex_x - 1;
	return (tex_x);
}

void	render_texture(t_game *game, int x)
{
	double			step;
	double			texpos;
	int				y;
	t_vectors		tex;
	unsigned int	color;

	tex.x = get_texture_x(game);
	step = 1.0 * game->walls[game->ray.color].width / game->ray.line_height;
	texpos = (game->ray.draw_start.y - SCREEN_H / 2
			+ game->ray.line_height / 2) * step;
	y = game->ray.draw_start.y - 1;
	draw_background(&game->data, game->ray.draw_start, game->ray.draw_end);
	while (++y < game->ray.draw_end.y)
	{
		tex.y = (int)texpos & (game->walls[game->ray.color].width - 1);
		texpos += step;
		color = *(unsigned int *)(game->walls[game->ray.color].addr
				+ 4 * (game->walls[game->ray.color].width
					* (int)tex.y + (int)tex.x));
		my_mlx_pixel_put(&game->data, x, y, color);
	}
}

void	door_animation(t_game *game)
{
	if (game->frames < (DOOR_FRAMES * 14))
		game->ray.color = 4;
	else if (game->frames < (DOOR_FRAMES * 23))
		game->ray.color = 5;
	else if (game->frames < (DOOR_FRAMES * 32))
		game->ray.color = 6;
	else if (game->frames < (DOOR_FRAMES * 41))
		game->ray.color = 7;
	else if (game->frames < (DOOR_FRAMES * 50))
		game->ray.color = 8;
	else if (game->frames < (DOOR_FRAMES * 59))
		game->ray.color = 9;
	else
	{
		game->ray.color = 1;
		game->frames = 0;
	}
}

void	select_texture(t_game *game)
{
	if (game->parser.map[game->ray.map_y][game->ray.map_x] == 'D')
	{
		door_animation(game);
	}
	else if (game->ray.side == 1 && game->player.pos.y <= game->ray.map_y)
		game->ray.color = 0;
	else if (game->ray.side == 1)
		game->ray.color = 1;
	else if (game->ray.side == 0 && game->player.pos.x <= game->ray.map_x)
		game->ray.color = 2;
	else if (game->ray.side == 0)
		game->ray.color = 3;
	else
		game->ray.color = 0;
}

void	draw_texture(t_game *game, int x)
{
	int	colors[4];

	select_texture(game);
	if (TEXTURES)
		render_texture(game, x);
	else
	{
		colors[0] = RGB_BLUE;
		colors[1] = RGB_GREEN;
		colors[2] = RGB_RED;
		colors[3] = RGB_YELLOW;
		draw_line_on(&game->data, game->ray.draw_start,
			game->ray.draw_end, colors[game->ray.color]);
	}
}
