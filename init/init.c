/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:32:03 by dcastagn          #+#    #+#             */
/*   Updated: 2023/08/04 13:59:59 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	find_player(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->parser.map[++y])
	{
		x = -1;
		while (game->parser.map[y][++x])
		{
			if (ft_strchr("NSWE", game->parser.map[y][x]))
			{
				game->player.pos.x = x + 0.5f;
				game->player.pos.y = y + 0.5f;
				return (1);
			}
		}
	}
	return (0);
}

void	startingpov(t_game *game)
{
	char	dir;

	dir = game->parser.map[(int)game->player.pos.y][
		(int)game->player.pos.x];
	if (dir == 'N')
	{
		game->player.dir.y = -1.0;
		game->player.plane.x = 0.66;
	}
	else if (dir == 'S')
	{
		game->player.dir.y = 1.0;
		game->player.plane.x = -0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir.x = -1.0;
		game->player.plane.y = -0.66;
	}
	else if (dir == 'E')
	{
		game->player.dir.x = 1.0;
		game->player.plane.y = 0.66;
	}
}

int	player_initialization(t_game *game)
{
	find_player(game);
	game->player.dir.x = 0.0;
	game->player.dir.y = 0.0;
	game->player.plane.x = 0.0;
	game->player.plane.y = 0.0;
	game->player.mov_dir.x = 0;
	game->player.mov_dir.y = 0;
	game->player.rot_dir = 0;
	game->x = SCREEN_W / 2;
	set_colors(game);
	startingpov(game);
	game->parser.map[(int)game->player.pos.y][(int)game->player.pos.x] = '0';
	return (0);
}

int	start_game(t_game *game)
{
	if (player_initialization(game))
		return (1);
	game->time = get_time();
	game->old_time = get_time();
	return (0);
}
