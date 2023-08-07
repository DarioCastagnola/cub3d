/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:15:09 by dcastagn          #+#    #+#             */
/*   Updated: 2023/08/07 14:57:29 by dcastagn         ###   ########.fr       */
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

void	render_texture2(t_game *game)
{
	game->tex.step = (double)game->walls[game->ray.color].width
		/ game->ray.line_height;
	game->tex.texpos = (game->ray.draw_start.y - SCREEN_H / 2
			+ game->ray.line_height / 2) * game->tex.step;
	draw_background(&game->data, game->ray.draw_start, game->ray.draw_end);
	game->tex.tex_width = game->walls[game->ray.color].width;
	game->tex.tex_height = game->walls[game->ray.color].height;
}

void	render_texture(t_game *game, int x)
{
	int				y;
	t_vectors		tex;
	unsigned int	color;

	tex.x = get_texture_x(game);
	render_texture2(game);
	y = game->ray.draw_start.y - 1;
	while (++y < game->ray.draw_end.y)
	{
		tex.y = (int)game->tex.texpos % game->tex.tex_height;
		game->tex.texpos += game->tex.step;
		if (tex.y < 0)
			tex.y += game->tex.tex_height;
		game->tex.tex_idx = (int)tex.x + game->tex.tex_width * tex.y;
		if (game->tex.tex_idx < 0)
			game->tex.tex_idx = 0;
		else if (game->tex.tex_idx >= game->tex.tex_width
			* game->tex.tex_height)
			game->tex.tex_idx = game->tex.tex_width * game->tex.tex_height - 1;
		color = *(unsigned int *)(game->walls[game->ray.color].addr + 4
				* game->tex.tex_idx);
		my_mlx_pixel_put(&game->data, x, y, color);
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
