/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:16:10 by lde-mich          #+#    #+#             */
/*   Updated: 2023/09/05 15:06:35 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_load_door_image(t_game *game)
{
	game->walls[4].img = mlx_xpm_file_to_image(game->mlx,
			"./maps/door/door_0.xpm", 
			&game->walls[4].width, &game->walls[4].height);
	game->walls[5].img = mlx_xpm_file_to_image(game->mlx,
			"./maps/door/door_1.xpm", 
			&game->walls[5].width, &game->walls[5].height);
	game->walls[6].img = mlx_xpm_file_to_image(game->mlx,
			"./maps/door/door_2.xpm", 
			&game->walls[6].width, &game->walls[6].height);
	game->walls[7].img = mlx_xpm_file_to_image(game->mlx,
			"./maps/door/door_4.xpm", 
			&game->walls[7].width, &game->walls[7].height);
	game->walls[8].img = mlx_xpm_file_to_image(game->mlx,
			"./maps/door/door_6.xpm", 
			&game->walls[8].width, &game->walls[8].height);
	game->walls[9].img = mlx_xpm_file_to_image(game->mlx,
			"./maps/door/door_7.xpm", 
			&game->walls[9].width, &game->walls[9].height);
}

int	ft_load_image(t_game *game, char **temp)
{
	if (!ft_strncmp(temp[0], "NO", 3))
		game->walls[0].img = mlx_xpm_file_to_image(game->mlx,
				temp[1], &game->walls[0].width, &game->walls[0].height);
	else if (!ft_strncmp(temp[0], "SO", 3))
		game->walls[1].img = mlx_xpm_file_to_image(game->mlx,
				temp[1], &game->walls[1].width, &game->walls[1].height);
	else if (!ft_strncmp(temp[0], "EA", 3))
		game->walls[2].img = mlx_xpm_file_to_image(game->mlx,
				temp[1], &game->walls[2].width, &game->walls[2].height);
	else if (!ft_strncmp(temp[0], "WE", 3))
		game->walls[3].img = mlx_xpm_file_to_image(game->mlx,
				temp[1], &game->walls[3].width, &game->walls[3].height);
	else
		return (0);
	return (1);
}
