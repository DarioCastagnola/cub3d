/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:21:01 by dcastagn          #+#    #+#             */
/*   Updated: 2023/08/04 16:36:42 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_mouse(int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	(void) y;
	mlx_mouse_hide(game->mlx, game->mlx_win);
	if (x > game->x)
		game->player.rot_dir = 1;
	if (x < game->x)
		game->player.rot_dir = -1;
	if (game->x == x || (((game->x + 5) > x) && (game->x - 5) < x))
		game->player.rot_dir = 0;
	game->x = x;
	if (game->x < 20 || game->x > SCREEN_W - 20)
		game->x = SCREEN_W / 2;
	return (0);
}

void	door_mechanics2(t_game *game)
{
	if (game->parser.map[(int)game->player.pos.y]
		[(int)(game->player.pos.x - 1)] == 'D')
		game->parser.map[(int)game->player.pos.y]
		[(int)game->player.pos.x - 1] = 'd';
	else if (game->parser.map[(int)game->player.pos.y]
		[(int)(game->player.pos.x + 1)] == 'D')
		game->parser.map[(int)game->player.pos.y]
		[(int)game->player.pos.x + 1] = 'd';
	else if (game->parser.map[(int)game->player.pos.y]
		[(int)game->player.pos.x - 1] == 'd')
		game->parser.map[(int)game->player.pos.y]
		[(int)game->player.pos.x - 1] = 'D';
	else if (game->parser.map[(int)game->player.pos.y]
		[(int)game->player.pos.x + 1] == 'd')
		game->parser.map[(int)game->player.pos.y]
		[(int)game->player.pos.x + 1] = 'D';
}

void	door_mechanics(t_game *game)
{
	if (game->parser.map[(int)game->player.pos.y - 1]
		[(int)(game->player.pos.x)] == 'D')
		game->parser.map[(int)game->player.pos.y - 1]
		[(int)game->player.pos.x] = 'd';
	else if (game->parser.map[(int)game->player.pos.y + 1]
		[(int)(game->player.pos.x)] == 'D')
		game->parser.map[(int)game->player.pos.y + 1]
		[(int)game->player.pos.x] = 'd';
	else if (game->parser.map[(int)game->player.pos.y - 1]
		[(int)game->player.pos.x] == 'd')
		game->parser.map[(int)game->player.pos.y - 1]
		[(int)game->player.pos.x] = 'D';
	else if (game->parser.map[(int)game->player.pos.y + 1]
		[(int)game->player.pos.x] == 'd')
		game->parser.map[(int)game->player.pos.y + 1]
		[(int)game->player.pos.x] = 'D';
	door_mechanics2(game);
}

int	key_hook_press(int key, t_game *game)
{
	if (key == 0 || key == 'a')
		game->player.mov_dir.y = -1;
	else if (key == 1 || key == 's')
		game->player.mov_dir.x = 1;
	else if (key == 2 || key == 'd')
		game->player.mov_dir.y = 1;
	else if (key == 13 || key == 'w')
		game->player.mov_dir.x = -1;
	else if (key == 65361)
		game->player.rot_dir = -1;
	else if (key == 65363)
		game->player.rot_dir = 1;
	else if (key == 32)
		door_mechanics(game);
	else if (key == 65307)
		ft_free_err(&game->parser, "Shutdown\n");
	return (0);
}

int	key_hook_release(int key, t_game *game)
{
	if (key == 'w' || key == 's')
		game->player.mov_dir.x = 0;
	else if (key == 'a' || key == 'd')
		game->player.mov_dir.y = 0;
	else if (key == 65363 || key == 65361)
		game->player.rot_dir = 0;
	return (0);
}
