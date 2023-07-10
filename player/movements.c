/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:21:01 by dcastagn          #+#    #+#             */
/*   Updated: 2023/07/10 10:33:54 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


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
	else if (key == 53 || key == 65307)
		exit(printf("wabba labba dub dub\n"));
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
