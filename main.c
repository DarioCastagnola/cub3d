/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:35:23 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/07 10:35:00 by dcastagn         ###   ########.fr       */
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
	exit(printf("YOU SHOULD KISS YOURSELF NOW!!\n"));
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
	    null_error("Wrong Input!!");
	ft_check_input(argv[1]);
	printf("ciao\n");
	printf("ciao1\n");
	initialization(&game);
	printf("ciao2\n");
	player_initialization(&game);
	printf("ciao3\n");
	mlx_hook(game.mlx_win, 17, 0, ft_destroy_window, &game);
	mlx_hook(game.mlx_win, 2, 1L<<0, key_hook, (void *)&game);
	mlx_loop_hook(game.mlx, draw_frames, (void *)&game);
	mlx_loop(game.mlx);
}
