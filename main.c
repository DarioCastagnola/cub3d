/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:35:23 by dcastagn          #+#    #+#             */
/*   Updated: 2023/06/30 16:39:29 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_input(char *s)
{
	int	l;

	l = ft_strlen(s);
	if (!(s[l - 1] == 'b' && s[l - 2] == 'u' && s[l - 3]
			== 'c' && s[l - 4] == '.'))
		null_error("Map isnt in .cub format");
}

int	ft_destroy_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(printf("The evil forces reign on\n"));
}

void	initialization(t_game *game)
{	
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window (game->mlx, SCREEN_W, SCREEN_H, "cub3d");
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
	    null_error("Wrong Input!!");
	ft_check_input(argv[1]);
	initialization(&game);
	mlx_hook(game.mlx_win, 17, 0, ft_destroy_window, &game);
	mlx_loop(game.mlx);
}

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
