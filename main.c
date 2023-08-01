/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:35:23 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/31 16:37:21 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_input(char *s)
{
	int	l;

	l = ft_strlen(s);
	if (!(s[l - 1] == 'b' && s[l - 2] == 'u' && s[l - 3]
			== 'c' && s[l - 4] == '.'))
		exit(write(2, "Error: Map isnt in .cub format\n", 24));
}

int	ft_destroy_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	ft_free_err(&game->parser, "Error: The evil forces reign on\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_parser	parser;

	game.mlx = mlx_init();
	parser.map = NULL;
	parser.readmap = NULL;
	if (argc != 2)
		exit(write(2, "Error: Inval1d input\n", 21));
	ft_check_input(argv[1]);
	ft_check_size(&parser, argv[1]);
	parser.readmap = ft_readmap(&parser, argv[1]);
	ft_map(&parser);
	ft_size_map(&parser);
	ft_check_fc(&parser);
	ft_check_texture(&parser, &game);
	ft_check_lmap(&parser);
	ft_check_map(&parser);
	ft_check_symbol_map(&parser);
	game.parser = parser;
	start_game(&game);
	init_game(&game);
	mlx_hook(game.mlx_win, 17, 0, ft_destroy_window, &game);
	mlx_hook(game.mlx_win, 2, 1L<<0, key_hook_press, (void *)&game);
	mlx_hook(game.mlx_win, 3, 1L<<1, key_hook_release, (void *)&game);
	mlx_hook(game.mlx_win, 6, 1L << 6, ft_mouse, (void *)&game);
	mlx_loop_hook(game.mlx, draw_frames, (void *)&game);
	mlx_loop(game.mlx);
}
