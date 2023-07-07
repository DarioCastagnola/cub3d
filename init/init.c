/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:32:03 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/07 10:36:57 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	find_player(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (ft_strchr("NSWE", map->map[y][x]))
			{
				map->player_pos.x = x;
				map->player_pos.y = y;
				return (1);
			}
		}
	}
	return (0);
}

int	find_player_inmap(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map.map[++y])
	{
		x = -1;
		while (game->map.map[y][++x])
		{
			if (ft_strchr("NSWE", game->map.map[y][x]))
				return (1);
		}
	}
	return (0);
}
void	initialization(t_game *game)
{	
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window (game->mlx, SCREEN_W, SCREEN_H, "cub3d");
}

void	startingpov(t_game *game)
{
	char	dir;

	dir = game->map.map[(int)game->map.player_pos.y][
		(int)game->map.player_pos.x];
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

int player_initialization(t_game *game)
{
    find_player(&game->map);
    game->player.pos.x = game->map.player_pos.x;
	game->player.pos.y = game->map.player_pos.y;
	game->player.dir.x = 0.0;
	game->player.dir.y = 0.0;
	game->player.plane.x = 0.0;
	game->player.plane.y = 0.0;
	game->player.mov_dir.x = 0;
	game->player.mov_dir.y = 0;
	game->player.rot_dir = 0;
	startingpov(game);
	game->map.map[(int)game->map.player_pos.y][(int)game->map.player_pos.x] = 0;
	if (find_player_inmap(game) == 1)
		null_error("Too Many Players");
	return (0);
}