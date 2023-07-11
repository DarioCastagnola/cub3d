/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:32:03 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/11 11:39:43 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	find_player(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->themap[++y])
	{
		x = -1;
		while (game->themap[y][++x])
		{
			if (ft_strchr("NSWE", game->themap[y][x]))
			{
				game->player.pos.x = x;
				game->player.pos.y = y;
				return (1);
			}
		}
	}
	return (0);
}

int	ft_multiplayer_inmap(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->themap[++y])
	{
		x = -1;
		while (game->themap[y][++x])
		{
			if (ft_strchr("NSWE", game->themap[y][x]))
				return (1);
		}
	}
	return (0);
}
void	initialization(t_game *game, char *file)
{
	(void)file;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window (game->mlx, SCREEN_W, SCREEN_H, "cub3d");
}

void	startingpov(t_game *game)
{
	char	dir;

	dir = game->themap[(int)game->player.pos.y][
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

int player_initialization(t_game *game)
{
	//ft_print_mat(game->themap);
	find_player(game);
	game->player.dir.x = 0.0;
	game->player.dir.y = 0.0;
	game->player.plane.x = 0.0;
	game->player.plane.y = 0.0;
	game->player.mov_dir.x = 0;
	game->player.mov_dir.y = 0;
	game->player.rot_dir = 0;
	startingpov(game);
	game->themap[(int)game->player.pos.y][(int)game->player.pos.x] = '0';
	ft_print_mat(game->themap);
	if (ft_multiplayer_inmap(game) == 1)
		null_error("Too Many Players");
	return (0);
}