/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:22:36 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/18 10:08:31 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_colliding(t_game *game, double y, double x)
{
	if (game->parser.map[(int)y][(int)x] == '0')
		return (0);
	if (game->parser.map[(int)y][(int)x] == 'O')
		return (0);
	if (game->parser.map[(int)y][(int)x] == 'D')
		return (0);
	return (1);
}

void	update_dir_x(t_game *game)
{
	if (game->player.mov_dir.x == -1)
	{
		if (!is_colliding(game, game->player.pos.y, game->player.pos.x
				+ game->player.dir.x * game->player.mov_speed.x))
			game->player.pos.x += game->player.dir.x * game->player.mov_speed.x;
		if (!is_colliding(game, game->player.pos.y + game->player.dir.y
				* game->player.mov_speed.x, game->player.pos.x))
			game->player.pos.y += game->player.dir.y * game->player.mov_speed.x;
	}
	else if (game->player.mov_dir.x == 1)
	{
		if (!is_colliding(game, game->player.pos.y, game->player.pos.x
				- game->player.dir.x * game->player.mov_speed.x))
			game->player.pos.x -= game->player.dir.x * game->player.mov_speed.x;
		if (!is_colliding(game, game->player.pos.y - game->player.dir.y
				* game->player.mov_speed.x, game->player.pos.x))
			game->player.pos.y -= game->player.dir.y * game->player.mov_speed.x;
	}
}

void	update_dir_y(t_game *game)
{
	if (game->player.mov_dir.y == 1)
	{
		if (!is_colliding(game, game->player.pos.y, game->player.pos.x
				- game->player.dir.y * game->player.mov_speed.y))
			game->player.pos.x -= game->player.dir.y * game->player.mov_speed.y;
		if (!is_colliding(game, game->player.pos.y + game->player.dir.x
				* game->player.mov_speed.y, game->player.pos.x))
			game->player.pos.y += game->player.dir.x * game->player.mov_speed.y;
	}
	else if (game->player.mov_dir.y == -1)
	{
		if (!is_colliding(game, game->player.pos.y, game->player.pos.x
				+ game->player.dir.y * game->player.mov_speed.y))
			game->player.pos.x += game->player.dir.y * game->player.mov_speed.y;
		if (!is_colliding(game, game->player.pos.y - game->player.dir.x
				* game->player.mov_speed.y, game->player.pos.x))
			game->player.pos.y -= game->player.dir.x * game->player.mov_speed.y;
	}
}

void	update_rot(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	rot_speed = 0;
	if (game->player.rot_dir == 1)
		rot_speed = game->player.rot_speed;
	else if (game->player.rot_dir == -1)
		rot_speed = -game->player.rot_speed;
	if (rot_speed)
	{
		game->player.dir.x = game->player.dir.x * cos(rot_speed)
			- game->player.dir.y * sin(rot_speed);
		game->player.dir.y = old_dir_x * sin(rot_speed)
			+ game->player.dir.y * cos(rot_speed);
		game->player.plane.x = game->player.plane.x * cos(
				rot_speed) - game->player.plane.y
			* sin(rot_speed);
		game->player.plane.y = old_plane_x * sin(rot_speed)
			+ game->player.plane.y * cos(rot_speed);
	}
}

void	update_time(t_game *game)
{
	char	*curr_fps;

	game->old_time = game->time;
	game->time = get_time();
	game->frame_time = (game->time - game->old_time) / 1000.0;
	game->fps = (int)(1.0 / game->frame_time);
	if (game->fps > 60)
	{
		ft_sleep(((1.0 / 60) - game->frame_time) * 1000);
		game->time = get_time();
		game->frame_time = (game->time - game->old_time) / 1000.0;
		game->fps = (int)(1.0 / game->frame_time);
	}
	curr_fps = ft_itoa(game->fps);
	mlx_string_put(game->mlx, game->mlx_win,
		20, 20, -1, curr_fps);
	free(curr_fps);
}

void	update_inputs(t_game *game)
{
    update_time(game);
	game->player.mov_speed.x = game->frame_time * 3.0;
	game->player.mov_speed.y = game->frame_time * 3.0;
	game->player.rot_speed = game->frame_time * 2.0;
	update_dir_x(game);
	update_dir_y(game);
	update_rot(game);
}