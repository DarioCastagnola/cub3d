/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:16:10 by lde-mich          #+#    #+#             */
/*   Updated: 2023/07/28 15:46:13 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_load_image(t_game *game, char **temp)
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
}

